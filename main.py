import os
import re
import json
import requests
import time
from sandbox_dockersimple import sandbox
import diff  # 这是用户的本地自定义模块
from pathlib import Path
import numpy as np
from datetime import datetime
import LLMTLE_token_edit_distance as DIS
from llm_api import LLMClient
import argparse
import traceback

continue_flag = {}
AC_flag = {}
llm = None  # 将在setup_llm_client中初始化

def load_progress_state(progress_file):
    """加载处理进度状态"""
    if os.path.exists(progress_file):
        try:
            with open(progress_file, 'r', encoding='utf-8') as f:
                return json.load(f)
        except:
            return {}
    return {}

def save_progress_state(progress_file, state):
    """保存处理进度状态"""
    try:
        # 先写入临时文件，然后重命名，确保原子操作
        temp_file = progress_file + '.tmp'
        with open(temp_file, 'w', encoding='utf-8') as f:
            json.dump(state, f, ensure_ascii=False, indent=2)
        
        # 原子性地替换文件
        if os.path.exists(progress_file):
            os.replace(temp_file, progress_file)
        else:
            os.rename(temp_file, progress_file)
    except Exception as e:
        print(f"警告: 保存进度文件失败: {str(e)}")
        # 清理临时文件
        temp_file = progress_file + '.tmp'
        if os.path.exists(temp_file):
            try:
                os.remove(temp_file)
            except:
                pass

def is_problem_solved(progress_state, problem_id, test_num):
    """检查某个问题是否已经解决过"""
    key = f"{problem_id}_{test_num}"
    return progress_state.get(key, {}).get('completed', False)

def mark_problem_completed(progress_state, problem_id, test_num, status):
    """标记某个问题已完成解决"""
    key = f"{problem_id}_{test_num}"
    progress_state[key] = {
        'completed': True,
        'status': status,
        'timestamp': datetime.now().isoformat()
    }

def parse_arguments():
    """解析命令行参数"""
    parser = argparse.ArgumentParser(description='LLM Algorithm Problem Solver Agent')
    
    # 必需参数
    parser.add_argument('--problems_path', type=str, required=True,
                       help='problems根路径 (如: problems)')
    parser.add_argument('--test_path', type=str, required=True,
                       help='test根路径 (如: test)')
    
    # 可选参数
    parser.add_argument('--output_dir', type=str, default='results',
                       help='输出目录 (默认: results)')
    parser.add_argument('--model', type=str, default='llama3',
                       help='使用的模型名称 (默认: llama3)')
    parser.add_argument('--test_num', type=int, default=1,
                       help='测试次数 (默认: 1)')
    parser.add_argument('--query_depth', type=int, default=1,
                       help='解决轮次 (默认: 1)')
    parser.add_argument('--see_data', action='store_true',
                       help='是否在错误反馈中包含测试数据')
    parser.add_argument('--backend', type=str, default='ollama',
                       choices=['ollama', 'openai', 'fastchat', 'vllm'],
                       help='LLM后端 (默认: ollama)')
    parser.add_argument('--api_key', type=str, default=None,
                       help='API密钥 (用于openai等)')
    parser.add_argument('--api_base', type=str, default=None,
                       help='API基础URL')
    parser.add_argument('--problem_filter', type=str, default=None,
                       help='只处理指定题目 (如: 1A,102B)')
    
    # 进度相关参数
    parser.add_argument('--clear_progress', action='store_true',
                       help='清除进度文件，重新开始')
    parser.add_argument('--show_progress', action='store_true',
                       help='显示当前进度并退出')
    
    args = parser.parse_args()
    
    # 参数验证
    if args.test_num < 1:
        parser.error("test_num 必须大于等于 1")
    
    if args.query_depth < 1:
        parser.error("query_depth 必须大于等于 1")
    
    # 对于某些后端，API密钥是必需的
    if args.backend in ['openai'] and not args.api_key and not os.getenv('LLM_API_KEY'):
        parser.error(f"使用 {args.backend} 后端需要提供 --api_key 或设置 LLM_API_KEY 环境变量")
    
    return args

def show_progress_status(args):
    """显示当前进度状态"""
    progress_file = os.path.join(args.output_dir, 'progress.json')
    progress_state = load_progress_state(progress_file)
    
    if not progress_state:
        print("没有找到进度记录")
        return
    
    print(f"进度状态 (文件: {progress_file}):")
    print(f"总完成任务数: {len(progress_state)}")
    print()
    
    # 按题目分组统计
    problems = {}
    for key, value in progress_state.items():
        parts = key.split('_')
        if len(parts) >= 2:
            problem_id = parts[0]
            test_num = parts[1]
            
            if problem_id not in problems:
                problems[problem_id] = []
            
            problems[problem_id].append({
                'test_num': test_num,
                'status': value.get('status', 'UNKNOWN'),
                'timestamp': value.get('timestamp', '')
            })
    
    # 显示统计
    for problem_id, tests in problems.items():
        print(f"题目 {problem_id}:")
        success_count = len([t for t in tests if t['status'] == 'SUCCESS'])
        total_count = len(tests)
        print(f"  成功解决: {success_count}/{total_count}")
        for test in tests:
            print(f"    测试 {test['test_num']}: {test['status']}")
        print()

def clear_progress_file(args):
    """清除进度文件"""
    progress_file = os.path.join(args.output_dir, 'progress.json')
    if os.path.exists(progress_file):
        os.remove(progress_file)
        print(f"已清除进度文件: {progress_file}")
    else:
        print("进度文件不存在")

def safe_single_solve(working_num, model_name, problem_id, query_depth, see_data_flag, output_dir, max_retries=3):
    """安全的单次问题解决，带重试机制"""
    for attempt in range(max_retries):
        try:
            print(f"    尝试 {attempt + 1}/{max_retries}: 解决题目 {problem_id}")
            result = single_solve(working_num, model_name, problem_id, 
                                query_depth, see_data_flag, output_dir)
            print(f"    成功完成: 题目 {problem_id}")
            return result, None
        except Exception as e:
            error_msg = f"尝试 {attempt + 1} 失败: {str(e)}"
            print(f"    {error_msg}")
            if attempt < max_retries - 1:
                wait_time = (attempt + 1) * 5  # 5, 10, 15秒等待
                print(f"    等待 {wait_time} 秒后重试...")
                time.sleep(wait_time)
            else:
                print(f"    最终失败: 题目 {problem_id} - {str(e)}")
                print(f"    跳过此任务，继续处理下一个...")
                # 返回一个表示失败的结果，而不是None
                # 格式: (query_list, ac_flag, distance, ac_code, conversation_id)
                error_result = (
                    [f"ERROR: {str(e)}"],  # query_list记录错误信息
                    0,  # ac_flag = 0 表示失败
                    -1,  # distance = -1 表示无法计算距离
                    None,  # ac_code = None 表示没有解决方案代码
                    None   # conversation_id = None 表示没有对话记录
                )
                return error_result, str(e)

def try_to_solve_with_progress(problem_id, model_name, test_num, query_depth, see_data_flag,
                             progress_state, progress_file, output_dir):
    """带进度保存的问题解决函数"""
    print(f"  开始解决题目: {problem_id}")
    
    for i in range(1, test_num + 1):
        # 检查是否已经处理过
        if is_problem_solved(progress_state, problem_id, i):
            print(f"    测试 {i}: 已处理，跳过")
            continue
        
        print(f"    开始测试 {i}/{test_num}")
        
        # 执行问题解决
        result, error = safe_single_solve(str(i), model_name, problem_id,
                                        query_depth, see_data_flag, output_dir)
        
        # safe_single_solve现在总是返回结果，不会返回None
        A, B, C, D, conv_id = result
        
        # 根据结果确定状态
        if error is not None:
            status = 'ERROR'
            print(f"    测试 {i}: ERROR ({error})")
        elif B == 1:
            status = 'SUCCESS'
            print(f"    测试 {i}: {status} (距离: {C if C >= 0 else 'N/A'})")
        else:
            status = 'FAILED'
            print(f"    测试 {i}: {status} (距离: {C if C >= 0 else 'N/A'})")
        
        # 立即记录结果
        log_result(
            problem_id=problem_id,
            test_num=i,
            query_depth=query_depth,
            model_name=model_name,
            status=status,
            pass_count=B,
            total_tests=1,
            min_distance=C if C >= 0 else -1,
            avg_distance=C if C >= 0 else -1,
            fix_rounds=len(A),
            error_types=[s for s in A if s != 'ACCEPT'] if error is None else [error],
            solution_code=D if B == 1 else None,
            conversation_id=conv_id,
            output_dir=output_dir
        )
        
        # 标记完成并保存进度
        mark_problem_completed(progress_state, problem_id, i, status)
        save_progress_state(progress_file, progress_state)
        
        print(f"    测试 {i}: 已保存进度")

def setup_llm_client(args):
    """根据参数设置LLM客户端"""
    global llm
    llm = LLMClient(
        backend=args.backend,
        api_key=args.api_key,
        api_base=args.api_base
    )

def setup_output_dirs(args):
    """设置输出目录"""
    os.makedirs(args.output_dir, exist_ok=True)
    os.makedirs('judge_files/code', exist_ok=True)
    os.makedirs('judge_files/response', exist_ok=True)
    os.makedirs('response_logs', exist_ok=True)

def get_available_problems(problems_path, test_path, problem_filter=None):
    """获取可用的题目列表"""
    available_problems = []
    
    # 获取problems下的所有题目
    if os.path.exists(problems_path):
        for problem_file in os.listdir(problems_path):
            if problem_file.endswith('.json'):
                problem_id = problem_file[:-5]  # 去掉.json后缀
                
                # 检查test目录是否存在
                test_dir = os.path.join(test_path, problem_id)
                has_tests = os.path.exists(test_dir) and os.listdir(test_dir)
                
                if has_tests:
                    available_problems.append(problem_id)
    
    # 如果指定了problem_filter，只返回匹配的题目
    if problem_filter:
        filter_list = problem_filter.split(',')
        available_problems = [p for p in available_problems if p in filter_list]
    
    return sorted(available_problems)

def run_batch_solve(args):
    """批量解决指定路径下的所有算法问题"""
    # 检查输入路径是否存在
    if not os.path.exists(args.problems_path):
        print(f"错误: problems路径不存在: {args.problems_path}")
        return
    
    if not os.path.exists(args.test_path):
        print(f"错误: test路径不存在: {args.test_path}")
        return
    
    # 设置输出目录
    setup_output_dirs(args)
    
    # 设置LLM客户端
    setup_llm_client(args)
    
    # 设置进度文件
    progress_file = os.path.join(args.output_dir, 'progress.json')
    progress_state = load_progress_state(progress_file)
    
    # 处理清理进度请求
    if args.clear_progress:
        clear_progress_file(args)
        return
    
    # 处理显示进度请求
    if args.show_progress:
        show_progress_status(args)
        return
    
    # 获取可用题目列表
    available_problems = get_available_problems(args.problems_path, args.test_path, args.problem_filter)
    
    if not available_problems:
        print("错误: 没有找到可用的题目")
        print(f"problems路径: {args.problems_path}")
        print(f"test路径: {args.test_path}")
        return
    
    print(f"开始批量解决算法问题:")
    print(f"  problems路径: {args.problems_path}")
    print(f"  test路径: {args.test_path}")
    print(f"  模型: {args.model}")
    print(f"  输出目录: {args.output_dir}")
    print(f"  进度文件: {progress_file}")
    print(f"  找到题目: {', '.join(available_problems)}")
    
    # 统计已完成的任务
    completed_count = len([k for k, v in progress_state.items() if v.get('completed', False)])
    if completed_count > 0:
        print(f"  已完成任务: {completed_count} 个")
    print()
    
    # 遍历每个题目
    for problem_id in available_problems:
        print(f"正在解决题目: {problem_id}")
        
        try:
            try_to_solve_with_progress(problem_id, args.model, 
                                     args.test_num, args.query_depth, args.see_data,
                                     progress_state, progress_file, args.output_dir)
            
            # 更新summary
            update_summary(problem_id, args.model, args.output_dir)
            
            print(f"  题目 {problem_id} 处理完成")
            
        except Exception as e:
            print(f"  题目 {problem_id} 处理失败: {str(e)}")
            print(f"  跳过此题目，继续处理下一个...")
            traceback.print_exc()
            
            # 可选：记录题目级别的错误
            error_log_file = os.path.join(args.output_dir, 'error_log.txt')
            with open(error_log_file, 'a', encoding='utf-8') as f:
                f.write(f"{datetime.now().isoformat()} - 题目 {problem_id} 处理失败: {str(e)}\n")
        
        print()
    
    print(f"批量问题解决完成!")
    print(f"  结果文件: {os.path.join(args.output_dir, 'solve_results.jsonl')}")
    print(f"  对话记录: {os.path.join(args.output_dir, 'conversation_logs.jsonl')}")
    print(f"  汇总统计: {os.path.join(args.output_dir, 'summary.json')}")
    print(f"  进度文件: {progress_file}")
    
    # 检查是否有错误日志
    error_log_file = os.path.join(args.output_dir, 'error_log.txt')
    if os.path.exists(error_log_file):
        print(f"  错误日志: {error_log_file}")
        # 统计错误数量
        with open(error_log_file, 'r', encoding='utf-8') as f:
            error_count = len(f.readlines())
        print(f"  总错误数: {error_count}")

def generate_conversation_id(problem_id, test_num):
    """生成对话ID，用于关联结果和对话记录"""
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    return f"{problem_id}_{test_num}_{timestamp}"

def log_conversation(conversation_id, round_num, role, content, judge_result=None, error_info=None, output_dir='.'):
    """记录对话到conversation_logs.jsonl"""
    conversation = {
        "conversation_id": conversation_id,
        "round": round_num,
        "role": role,  # "user", "assistant", "system"
        "content": content,
        "timestamp": datetime.now().isoformat(),
        "judge_result": judge_result,  # 判题结果：ACCEPT, WA, TLE, RE等
        "error_info": error_info  # 错误信息：如WA时的具体测试用例
    }
    conversation_file = os.path.join(output_dir, 'conversation_logs.jsonl')
    with open(conversation_file, 'a', encoding='utf-8') as f:
        f.write(json.dumps(conversation, ensure_ascii=False) + '\n')

def log_result(problem_id, test_num, query_depth, model_name, 
               status, pass_count, total_tests, min_distance, avg_distance, 
               fix_rounds, error_types, solution_code=None, conversation_id=None, output_dir='.'):
    """统一记录结果到solve_results.jsonl"""
    result = {
        "problem_id": problem_id,
        "test_num": test_num,
        "query_depth": query_depth,
        "model_name": model_name,
        "timestamp": datetime.now().isoformat(),
        "status": status,
        "pass_count": pass_count,
        "total_tests": total_tests,
        "min_distance": min_distance,
        "avg_distance": avg_distance,
        "fix_rounds": fix_rounds,
        "error_types": error_types,
        "solution_code": solution_code,
        "conversation_id": conversation_id  # 关联对话记录
    }
    results_file = os.path.join(output_dir, 'solve_results.jsonl')
    with open(results_file, 'a', encoding='utf-8') as f:
        f.write(json.dumps(result, ensure_ascii=False) + '\n')

def update_summary(problem_id, model_name, output_dir='.'):
    """更新summary.json统计信息"""
    summary_file = os.path.join(output_dir, 'summary.json')
    
    # 读取现有的summary
    summary = {}
    if os.path.exists(summary_file):
        try:
            with open(summary_file, 'r', encoding='utf-8') as f:
                summary = json.load(f)
        except:
            summary = {}
    
    # 从solve_results.jsonl重新计算统计信息
    results_file = os.path.join(output_dir, 'solve_results.jsonl')
    if os.path.exists(results_file):
        with open(results_file, 'r', encoding='utf-8') as f:
            results = [json.loads(line) for line in f if line.strip()]
        
        # 按problem_id分组统计
        problem_stats = {}
        for result in results:
            pid = result['problem_id']
            if pid not in problem_stats:
                problem_stats[pid] = {
                    'total_tests': 0,
                    'successful_solutions': 0,
                    'failed_solutions': 0,
                    'error_count': 0,
                    'avg_distance': 0,
                    'min_distance': float('inf'),
                    'distances': []
                }
            
            stats = problem_stats[pid]
            stats['total_tests'] += 1
            
            if result['status'] == 'SUCCESS':
                stats['successful_solutions'] += 1
                if result['min_distance'] >= 0:
                    stats['distances'].append(result['min_distance'])
                    if result['min_distance'] < stats['min_distance']:
                        stats['min_distance'] = result['min_distance']
            elif result['status'] == 'FAILED':
                stats['failed_solutions'] += 1
            elif result['status'] == 'ERROR':
                stats['error_count'] += 1
        
        # 计算平均距离
        for pid, stats in problem_stats.items():
            if stats['distances']:
                stats['avg_distance'] = sum(stats['distances']) / len(stats['distances'])
                stats['success_rate'] = stats['successful_solutions'] / stats['total_tests']
            else:
                stats['min_distance'] = -1
                stats['success_rate'] = 0
        
        summary['problems'] = problem_stats
        summary['last_updated'] = datetime.now().isoformat()
        summary['model'] = model_name
    
    # 保存summary
    with open(summary_file, 'w', encoding='utf-8') as f:
        json.dump(summary, f, ensure_ascii=False, indent=2)

# 新的prompt模板 - 用于解决算法问题
begin_prompt = """Here is a programming problem you need to solve. Please analyze the problem and provide a complete solution. \n"""

question = """\nQuestion: Please provide a complete solution to this problem. \n"""

TLE_prompt = """This solution did not finish running within the time limit. Please optimize the algorithm to reduce time complexity and output the improved solution."""

RE_prompt = """This solution may have syntax errors, logical errors, or runtime issues. Please fix the errors and output the corrected solution."""

MLE_prompt = """This solution uses too much memory. Please optimize the memory usage and output the improved solution."""

WA_prompt = """This solution outputs the wrong result. Please fix the algorithm logic and output the corrected solution."""

UKE_prompt = """There are unknown errors in this solution. Please fix the errors and output the corrected solution."""

def remove_comments(_str):
    # A very basic function to remove the comments from the code
    new_str = ""
    list_str = _str.split('\n')
    for line in list_str:
        if line.startswith("#"):
            continue
        else:
            if line != "":
                new_str += line + "\n"
    return (new_str)

def get_prompt(problem_id):
    """从problems目录读取题目信息并生成prompt"""
    problem_path = os.path.join('problems', f'{problem_id}.json')
    with open(problem_path, 'r', encoding='utf-8') as f:
        problem_info = json.load(f)
    description = problem_info.get('description', '')
    hints = problem_info.get('hints', '')
    example_prompt = begin_prompt + description + question
    if hints:
        example_prompt = example_prompt + "\nHints: " + hints
    return example_prompt

def res2code():
    print("开始提取代码...")
    codes = ''
    try:
        with open('judge_files/response/response.txt', encoding='utf-8') as f1:
            print("成功打开响应文件")
            while (True):
                str = f1.readline()
                if not str:
                    print("到达文件末尾")
                    break
                if str[0:3] == '```':
                    print("找到代码块开始标记")
                    break
            f2 = open('judge_files/code/main.py', 'w', encoding='utf-8')
            print("开始写入代码文件...")
            while (True):
                str = f1.readline()
                if not str or str[0:3] == '```':
                    print("代码块结束")
                    break
                f2.write(str)
                codes = codes + str
                # print(str)
            f2.close()
            print(f"代码提取完成，长度: {len(codes)}")
    except Exception as e:
        print(f"res2code函数出错: {str(e)}")
        codes = ""
    # print(codes)
    return codes

def get_wa_prompt(problem_id, test_id, data_flag):
    if (data_flag == 0):
        wa_prompt = """This solution outputs the wrong result. Please fix this error and output the corrected solution."""
        return wa_prompt
    with open('test/' + problem_id + '/' + str(test_id) + '.in', encoding='utf-8') as f:
        input = f.read()
    with open('test/' + problem_id + '/' + str(test_id) + '.ans', encoding='utf-8') as f:
        ans = f.read()
    wa_prompt = """This solution outputs the wrong result. In test case """ + input + """  The correct result is  """ + ans + """  Please fix this error and output the corrected solution."""
    return wa_prompt

def judge_problem(problem_id):
    print(f"开始判题，题目: {problem_id}")
    now = int(time.time())
    container = 'J' + time.strftime(r"%Y%m%d_%H%M%S", time.localtime(now))
    print(f"容器名称: {container}")
    maxn = 0
    for i in range(1, 1000):
        if not os.path.exists('test/' + problem_id + '/' + str(i) + '.in'):
            maxn = i
            break
    print(f"题目 {problem_id} 有 {maxn-1} 个测试用例")
    # print(problem_id + " have only " + str(maxn) + " tests")
    s = sandbox()
    print("创建sandbox容器...")
    s.create(container, 'python', 'judge_files/code', 'test/' + problem_id)
    print("开始执行测试...")
    for i in range(1, maxn):
        print(f"执行测试 {i}...")
        if (problem_id == '584A'):
            ans = s.run('python main.py', str(i), problem_id='584A')
        else:
            ans = s.run('python main.py', str(i))
        print(f"测试 {i} 结果: {ans}")
        if not ans == 'ACCEPT':
            print(f"测试失败，清理容器...")
            s.remove()
            return ans, i
    print("所有测试通过，清理容器...")
    s.remove()
    return 'ACCEPT', 0

def judge_problem_cpp(problem_id, tag):
    now = datetime.now()
    milliseconds = now.microsecond // 1000
    container = 'J' + time.strftime(r"%Y%m%d_%H%M%S", time.localtime(milliseconds))
    container = container + "_" + tag
    maxn = 0
    for i in range(1, 1000):
        if not os.path.exists('test/' + problem_id + '/' + str(i) + '.in'):
            maxn = i
            break
    # print(problem_id + " have only " + str(maxn) + " tests")
    s = sandbox()
    s.create(container, 'gcc', 'judge_files/code', 'test/' + problem_id)
    try:
        s.compile('g++ main.cpp -o main -O3')
    except:
        s.remove()
        return 'CE', 0
    # s.create(container, 'python', 'gcc', 'judge_files/code', 'test/' + problem_id)
    for i in range(1, maxn):
        if (problem_id == '584A'):
            ans = s.run('./main', str(i), problem_id='584A')
        else:
            ans = s.run('./main', str(i))
        if not ans == 'ACCEPT':
            s.remove()
            return ans, i
    s.remove()
    return 'ACCEPT', 0

def single_solve(working_num, model_name, problem_id, query_depth, see_data_flag, output_dir):
    global llm
    if llm is None:
        # 如果LLM还未初始化，使用默认配置
        llm = LLMClient(backend="ollama")
    
    print("working on problem " + problem_id + ":")
    base_prompt = get_prompt(problem_id)
    
    # 生成对话ID
    conversation_id = generate_conversation_id(problem_id, working_num)
    
    # 记录初始prompt
    log_conversation(conversation_id, 0, "user", base_prompt, output_dir=output_dir)
    
    messages = [
        {
            "role": "user",
            "content": base_prompt
        }
    ]
    data = {
        "model": model_name,
        "messages": messages,
        "stream": False
    }
    query_list = []
    ac_flag = 0
    ac_code = ''
    for i in range(query_depth):
        response_content = llm.generate(base_prompt, model=model_name)
        print("Got response" + str(i))
        print(f"LLM响应长度: {len(response_content)} 字符")
        messages.append({"role": "assistant", "content": response_content})
        
        # 记录LLM回复
        log_conversation(conversation_id, i+1, "assistant", response_content, output_dir=output_dir)
        
        print("正在保存响应到文件...")
        with open('judge_files/response/response.txt', 'w', encoding='utf-8') as output:
            output.write(response_content)
        with open('response_logs/response_log_' + problem_id + "_" + working_num + '.txt',
                  'a', encoding='utf-8') as output:
            print("assistant" + str(i) + ":", file=output)
            print(response_content, file=output)
            print("=========end==========\n", file=output)
        
        print("正在提取代码...")
        newcode = res2code()
        print(f"提取的代码长度: {len(newcode)} 字符")
        
        print("正在执行判题...")
        judge_statue, fail_num = judge_problem(problem_id)
        print(f"判题结果: {judge_statue}, 失败测试: {fail_num}")
        query_list.append(judge_statue)
        
        # 记录判题结果
        error_info = None
        if judge_statue == 'WRONG ANSWER' and see_data_flag:
            error_info = f"WA on test {fail_num}"
        elif judge_statue != 'ACCEPT':
            error_info = f"{judge_statue}"
        
        log_conversation(conversation_id, i+1, "system", f"Judge result: {judge_statue}", 
                         judge_result=judge_statue, error_info=error_info, output_dir=output_dir)
        
        if judge_statue == 'ACCEPT':
            ac_flag = 1
            ac_code = newcode
            break
        elif judge_statue == 'MEMORY LIMIT EXECEED':
            new_prompt = {
                'role': 'user',
                'content': MLE_prompt
            }
        elif judge_statue == 'TIME LIMIT EXECEED':
            new_prompt = {
                'role': 'user',
                'content': TLE_prompt
            }
        elif judge_statue == 'RUNTIME ERROR':
            new_prompt = {
                'role': 'user',
                'content': RE_prompt
            }
        elif judge_statue == 'WRONG ANSWER':
            new_prompt = {
                'role': 'user',
                'content': get_wa_prompt(problem_id, fail_num, see_data_flag)
            }
        messages.append(new_prompt)
        
        # 记录错误反馈
        log_conversation(conversation_id, i+1, "user", new_prompt['content'], 
                         judge_result=judge_statue, error_info=error_info, output_dir=output_dir)

        with open('response_logs/response_log_' + problem_id + "_" + working_num + '.txt',
                  'a') as output:
            print("user" + str(i) + ":", file=output)
            print(new_prompt['content'], file=output)
            print("=========end==========\n", file=output)
    
    if ac_flag == 1:
        # 计算与原始prompt的距离（这里可以自定义距离计算方式）
        distance = 0  # 简化处理，因为不再有原始代码
        with open('response_logs/response_log_' + problem_id + "_" + working_num + '.txt',
                  'a') as output:
            print("AC: Solution found successfully", file=output)
    else:
        distance = -1
    print(query_list)
    return query_list, ac_flag, distance, ac_code, conversation_id

def main():
    """原有的批量处理功能"""
    model_name = "llama3"
    test_num = 1
    query_depth = 1
    see_data_flag = False

    problem_name = "1A"
    # 现在直接解决问题，不需要submissions目录
    print(f"开始解决题目: {problem_name}")
    try_to_solve_with_progress(problem_name, model_name, test_num, query_depth, see_data_flag, {}, 'progress.json', '.')

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        # 命令行参数模式
        args = parse_arguments()
        
        # 处理特殊命令
        if args.clear_progress or args.show_progress:
            # 确保输出目录存在
            os.makedirs(args.output_dir, exist_ok=True)
            
            if args.clear_progress:
                clear_progress_file(args)
            elif args.show_progress:
                show_progress_status(args)
        else:
            # 正常批量问题解决
            run_batch_solve(args)
    else:
        # 原有的批量处理模式
        main()
