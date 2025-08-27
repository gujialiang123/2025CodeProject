import os
import uuid
import shutil
from typing import Dict, Any, Tuple
from datetime import datetime

from sandbox_dockersimple import sandbox


class AlgorithmSolveEnv:
    """
    最小可用的RL环境：
    - reset(problem_id) -> observation(dict)
    - step(action_code_str) -> (observation, reward, done, info)
    说明：
    - 仅负责判题与反馈，不进行LLM调用。
    - 使用临时工作目录与唯一容器名，支持并发。
    - 根据判题结果生成奖励与下一轮提示（observation['feedback']）。
    """

    def __init__(self, problems_dir: str = 'problems', tests_root: str = 'test', see_data: bool = False,
                 max_rounds: int = 3, language: str = 'python') -> None:
        self.problems_dir = problems_dir
        self.tests_root = tests_root
        self.see_data = see_data
        self.max_rounds = max_rounds
        self.language = language
        self._round = 0
        self._problem_id: str = ''
        self._workdir: str = ''

    def reset(self, problem_id: str) -> Dict[str, Any]:
        self._round = 0
        self._problem_id = problem_id
        # 读取题目描述
        import json
        with open(os.path.join(self.problems_dir, f'{problem_id}.json'), 'r', encoding='utf-8') as f:
            problem_info = json.load(f)
        # observation: 题目描述与提示
        obs = {
            'problem_id': problem_id,
            'description': problem_info.get('description', ''),
            'hints': problem_info.get('hints', ''),
            'round': self._round
        }
        return obs

    def close(self) -> None:
        # 清理工作目录（如果有）
        if self._workdir and os.path.exists(self._workdir):
            shutil.rmtree(self._workdir, ignore_errors=True)
        self._workdir = ''

    def _prepare_workspace(self) -> Tuple[str, str, str]:
        """创建唯一工作目录，返回(code_dir, test_dir, container_name)"""
        if not self._workdir:
            uid = uuid.uuid4().hex[:8]
            self._workdir = os.path.abspath(os.path.join('run', f'rl_{self._problem_id}_{uid}'))
            os.makedirs(self._workdir, exist_ok=True)
        code_dir = os.path.join(self._workdir, 'code')
        test_dir = os.path.join(self._workdir, 'test')
        os.makedirs(code_dir, exist_ok=True)
        os.makedirs(test_dir, exist_ok=True)
        # 复制测试用例
        src_test = os.path.join(self.tests_root, self._problem_id)
        if not os.path.isdir(src_test):
            raise FileNotFoundError(f'test dir not found: {src_test}')
        # 目标为空目录，复制全部测试
        shutil.copytree(src_test, test_dir, dirs_exist_ok=True)
        # 容器名
        container = 'R' + datetime.now().strftime('%Y%m%d_%H%M%S') + '_' + uuid.uuid4().hex[:6]
        return code_dir, test_dir, container

    def _write_code(self, code_dir: str, code: str) -> str:
        if self.language == 'python':
            target = os.path.join(code_dir, 'main.py')
        else:
            target = os.path.join(code_dir, 'main.cpp')
        with open(target, 'w', encoding='utf-8') as f:
            f.write(code)
        return target

    def _judge(self, code_dir: str, test_dir: str, container: str) -> Tuple[str, int]:
        s = sandbox()
        if self.language == 'python':
            s.create(container, 'python', code_dir, test_dir)
            # 统计测试文件数量
            maxn = 0
            for i in range(1, 1000):
                if not os.path.exists(os.path.join(test_dir, f'{i}.in')):
                    maxn = i
                    break
            for i in range(1, maxn):
                if self._problem_id == '584A':
                    status = s.run('python main.py', str(i), problem_id='584A')
                else:
                    status = s.run('python main.py', str(i))
                if status != 'ACCEPT':
                    s.remove()
                    return status, i
            s.remove()
            return 'ACCEPT', 0
        else:
            s.create(container, 'gcc', code_dir, test_dir)
            try:
                s.compile('g++ main.cpp -o main -O3')
            except Exception:
                s.remove()
                return 'COMPILE ERROR', 0
            maxn = 0
            for i in range(1, 1000):
                if not os.path.exists(os.path.join(test_dir, f'{i}.in')):
                    maxn = i
                    break
            for i in range(1, maxn):
                if self._problem_id == '584A':
                    status = s.run('./main', str(i), problem_id='584A')
                else:
                    status = s.run('./main', str(i))
                if status != 'ACCEPT':
                    s.remove()
                    return status, i
            s.remove()
            return 'ACCEPT', 0

    @staticmethod
    def _reward_from_status(status: str, pass_ratio: float = 0.0) -> float:
        if status == 'ACCEPT':
            return 1.0
        if status == 'WRONG ANSWER':
            return 0.0 + pass_ratio * 0.5
        if status in ('TIME LIMIT EXECEED', 'MEMORY LIMIT EXECEED', 'RUNTIME ERROR', 'COMPILE ERROR'):
            return -0.2
        return 0.0

    def step(self, action_code: str) -> Tuple[Dict[str, Any], float, bool, Dict[str, Any]]:
        self._round += 1
        code_dir, test_dir, container = self._prepare_workspace()
        self._write_code(code_dir, action_code)
        status, fail_id = self._judge(code_dir, test_dir, container)
        # 估算通过比例
        total_tests = len([f for f in os.listdir(test_dir) if f.endswith('.in')])
        passed = total_tests if status == 'ACCEPT' else (fail_id - 1 if fail_id > 0 else 0)
        pass_ratio = (passed / total_tests) if total_tests > 0 else 0.0
        reward = self._reward_from_status(status, pass_ratio)
        done = (status == 'ACCEPT') or (self._round >= self.max_rounds)
        # 反馈文本（供下一轮policy参考）
        if status == 'WRONG ANSWER':
            feedback = f"WA on test {fail_id}"
            if self.see_data:
                try:
                    with open(os.path.join(test_dir, f'{fail_id}.in'), 'r', encoding='utf-8') as fi:
                        in_txt = fi.read()
                    with open(os.path.join(test_dir, f'{fail_id}.ans'), 'r', encoding='utf-8') as fo:
                        out_txt = fo.read()
                    feedback += f"\nInput:\n{in_txt}\nExpected:\n{out_txt}"
                except Exception:
                    pass
        else:
            feedback = status
        obs = {
            'problem_id': self._problem_id,
            'round': self._round,
            'feedback': feedback
        }
        info = {
            'status': status,
            'fail_test_id': fail_id,
            'pass_ratio': pass_ratio,
            'total_tests': total_tests
        }
        return obs, reward, done, info
