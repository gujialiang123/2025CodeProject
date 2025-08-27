#!/usr/bin/env python3
"""
演示脚本：展示LLM算法问题解决Agent的使用方法
"""

import os
import json
import subprocess
import sys

def create_demo_problem():
    """创建演示题目"""
    print("📝 创建演示题目...")
    
    # 创建problems目录
    os.makedirs('problems', exist_ok=True)
    
    # 创建几个简单的算法题目
    problems = {
        "DEMO1": {
            "id": "DEMO1",
            "title": "Maximum of Two Numbers",
            "description": "Given two integers a and b, find the maximum of them.\n\nInput:\nThe first line contains two integers a and b (-1000 ≤ a, b ≤ 1000).\n\nOutput:\nPrint the maximum of a and b.",
            "hints": "Use the built-in max() function or compare the numbers.",
            "samples": []
        },
        "DEMO2": {
            "id": "DEMO2", 
            "title": "Sum of Array",
            "description": "Given an array of n integers, calculate the sum of all elements.\n\nInput:\nThe first line contains an integer n (1 ≤ n ≤ 100).\nThe second line contains n space-separated integers a1, a2, ..., an (-1000 ≤ ai ≤ 1000).\n\nOutput:\nPrint the sum of all array elements.",
            "hints": "Use a loop to iterate through the array and accumulate the sum.",
            "samples": []
        }
    }
    
    for problem_id, problem_data in problems.items():
        with open(f'problems/{problem_id}.json', 'w', encoding='utf-8') as f:
            json.dump(problem_data, f, ensure_ascii=False, indent=2)
        print(f"  ✅ 创建题目: {problem_id}")
    
    return list(problems.keys())

def create_demo_test_cases():
    """创建演示测试用例"""
    print("🧪 创建演示测试用例...")
    
    # 创建test目录
    os.makedirs('test', exist_ok=True)
    
    # DEMO1的测试用例
    os.makedirs('test/DEMO1', exist_ok=True)
    test_cases_demo1 = [
        ("5 3", "5"),
        ("3 5", "5"), 
        ("-1 -5", "-1"),
        ("0 0", "0")
    ]
    
    for i, (input_data, expected_output) in enumerate(test_cases_demo1, 1):
        with open(f'test/DEMO1/{i}.in', 'w') as f:
            f.write(input_data)
        with open(f'test/DEMO1/{i}.ans', 'w') as f:
            f.write(expected_output)
    
    print(f"  ✅ 创建DEMO1测试用例: {len(test_cases_demo1)}个")
    
    # DEMO2的测试用例
    os.makedirs('test/DEMO2', exist_ok=True)
    test_cases_demo2 = [
        ("3\n1 2 3", "6"),
        ("4\n-1 2 -3 4", "2"),
        ("1\n100", "100"),
        ("5\n0 0 0 0 0", "0")
    ]
    
    for i, (input_data, expected_output) in enumerate(test_cases_demo2, 1):
        with open(f'test/DEMO2/{i}.in', 'w') as f:
            f.write(input_data)
        with open(f'test/DEMO2/{i}.ans', 'w') as f:
            f.write(expected_output)
    
    print(f"  ✅ 创建DEMO2测试用例: {len(test_cases_demo2)}个")

def show_usage_examples():
    """显示使用示例"""
    print("\n🚀 系统使用示例:")
    print("=" * 50)
    
    examples = [
        {
            "description": "解决单个题目（DEMO1）",
            "command": "python main.py --problems_path problems --test_path test --problem_filter DEMO1 --model llama3 --query_depth 2"
        },
        {
            "description": "解决多个题目",
            "command": "python main.py --problems_path problems --test_path test --problem_filter DEMO1,DEMO2 --model llama3 --query_depth 3"
        },
        {
            "description": "查看当前进度",
            "command": "python main.py --problems_path problems --test_path test --show_progress"
        },
        {
            "description": "清除进度重新开始",
            "command": "python main.py --problems_path problems --test_path test --clear_progress"
        }
    ]
    
    for i, example in enumerate(examples, 1):
        print(f"{i}. {example['description']}")
        print(f"   命令: {example['command']}")
        print()

def check_ollama_status():
    """检查Ollama状态"""
    print("🔍 检查Ollama状态...")
    
    try:
        # 检查ollama命令是否可用
        result = subprocess.run(['ollama', 'list'], capture_output=True, text=True, timeout=10)
        if result.returncode == 0:
            print("  ✅ Ollama运行正常")
            print("  可用模型:")
            for line in result.stdout.strip().split('\n')[1:]:  # 跳过标题行
                if line.strip():
                    print(f"    {line.strip()}")
        else:
            print("  ⚠️  Ollama命令执行失败")
            print("  请确保Ollama已安装并运行")
    except FileNotFoundError:
        print("  ❌ Ollama未安装")
        print("  请先安装Ollama: https://ollama.ai/")
    except subprocess.TimeoutExpired:
        print("  ⚠️  Ollama响应超时")
    except Exception as e:
        print(f"  ❌ 检查Ollama时出错: {e}")

def run_demo():
    """运行演示"""
    print("🎯 开始演示LLM算法问题解决Agent")
    print("=" * 60)
    
    # 检查Ollama状态
    check_ollama_status()
    
    # 创建演示环境
    problem_ids = create_demo_problem()
    create_demo_test_cases()
    
    print(f"\n📁 演示环境创建完成！")
    print(f"  题目: {', '.join(problem_ids)}")
    print(f"  测试用例: test/目录")
    
    # 显示使用示例
    show_usage_examples()
    
    # 询问是否立即运行
    try:
        response = input("\n是否立即运行演示？(y/n): ").lower().strip()
        if response in ['y', 'yes', '是']:
            print("\n🚀 开始运行演示...")
            
            # 运行DEMO1
            print("\n📝 解决题目: DEMO1")
            cmd = [
                sys.executable, 'main.py',
                '--problems_path', 'problems',
                '--test_path', 'test',
                '--problem_filter', 'DEMO1',
                '--model', 'llama3',
                '--query_depth', '2',
                '--output_dir', 'demo_results'
            ]
            
            print(f"执行命令: {' '.join(cmd)}")
            
            try:
                result = subprocess.run(cmd, timeout=300)  # 5分钟超时
                if result.returncode == 0:
                    print("✅ 演示运行完成！")
                    print("查看结果文件: demo_results/")
                else:
                    print(f"⚠️  演示运行结束，退出码: {result.returncode}")
            except subprocess.TimeoutExpired:
                print("⏰ 演示运行超时（5分钟）")
            except KeyboardInterrupt:
                print("\n⏹️  演示被用户中断")
            except Exception as e:
                print(f"❌ 运行演示时出错: {e}")
        else:
            print("\nℹ️  跳过运行，可以稍后手动执行命令")
            
    except KeyboardInterrupt:
        print("\nℹ️  跳过运行")

def cleanup_demo():
    """清理演示文件"""
    print("\n🧹 清理演示文件...")
    
    import shutil
    
    # 删除演示目录
    demo_dirs = ['problems', 'test', 'demo_results']
    for dir_name in demo_dirs:
        if os.path.exists(dir_name):
            shutil.rmtree(dir_name)
            print(f"  ✅ 删除目录: {dir_name}")

def main():
    """主函数"""
    print("🎉 欢迎使用LLM算法问题解决Agent演示系统！")
    
    try:
        run_demo()
        
    except Exception as e:
        print(f"\n❌ 演示过程中出现错误: {e}")
        import traceback
        traceback.print_exc()
    
    finally:
        # 询问是否清理
        try:
            response = input("\n是否清理演示文件？(y/n): ").lower().strip()
            if response in ['y', 'yes', '是']:
                cleanup_demo()
                print("✅ 演示文件已清理")
            else:
                print("ℹ️  演示文件保留，可以继续使用")
        except KeyboardInterrupt:
            print("\nℹ️  跳过清理")

if __name__ == "__main__":
    main()
