import os
import uuid
import shutil
from typing import Dict, Any, Tuple
from datetime import datetime

from sandbox_dockersimple import sandbox


def judge_code(problem_id: str, code: str, tests_root: str = 'test', language: str = 'python') -> Dict[str, Any]:
    """
    直接对给定代码字符串进行判题，返回结构化结果：
    {
      'status': 'ACCEPT'|'WRONG ANSWER'|..., 'fail_test_id': int, 'total_tests': int
    }
    """
    # 准备临时目录
    uid = uuid.uuid4().hex[:8]
    workdir = os.path.abspath(os.path.join('run', f'judge_{problem_id}_{uid}'))
    code_dir = os.path.join(workdir, 'code')
    test_dir = os.path.join(workdir, 'test')
    os.makedirs(code_dir, exist_ok=True)
    os.makedirs(test_dir, exist_ok=True)
    try:
        # 写代码
        if language == 'python':
            code_path = os.path.join(code_dir, 'main.py')
        else:
            code_path = os.path.join(code_dir, 'main.cpp')
        with open(code_path, 'w', encoding='utf-8') as f:
            f.write(code)
        # 复制测试
        src_test = os.path.join(tests_root, problem_id)
        if not os.path.isdir(src_test):
            raise FileNotFoundError(f'test dir not found: {src_test}')
        shutil.copytree(src_test, test_dir, dirs_exist_ok=True)
        # 判题
        s = sandbox()
        container = 'R' + datetime.now().strftime('%Y%m%d_%H%M%S') + '_' + uid
        if language == 'python':
            s.create(container, 'python', code_dir, test_dir)
        else:
            s.create(container, 'gcc', code_dir, test_dir)
            try:
                s.compile('g++ main.cpp -o main -O3')
            except Exception:
                s.remove()
                return {'status': 'COMPILE ERROR', 'fail_test_id': 0, 'total_tests': 0}
        maxn = 0
        for i in range(1, 1000):
            if not os.path.exists(os.path.join(test_dir, f'{i}.in')):
                maxn = i
                break
        total = max(0, maxn - 1)
        for i in range(1, maxn):
            if problem_id == '584A':
                status = s.run('python main.py' if language == 'python' else './main', str(i), problem_id='584A')
            else:
                status = s.run('python main.py' if language == 'python' else './main', str(i))
            if status != 'ACCEPT':
                s.remove()
                return {'status': status, 'fail_test_id': i, 'total_tests': total}
        s.remove()
        return {'status': 'ACCEPT', 'fail_test_id': 0, 'total_tests': total}
    finally:
        shutil.rmtree(workdir, ignore_errors=True)
