import os
import signal
import diff as difflib
import time
import shutil

class sandbox:
    def create(self, container_name, image_name, code_folder, test_folder, silence=False, reset_before_run=True):
        self.container_name = container_name
        self.image_name = image_name
        self.code_folder = code_folder
        self.silence = silence
        self.reset_before_run = reset_before_run
        self.last_total_time_used_ms = 0
        self.first_run = True
        self.compiled = False
        self.docker_created = False
        # 只支持目录模式
        if not os.path.isdir(code_folder):
            raise NotADirectoryError(code_folder + " is not a directory")
        if not os.path.isdir(test_folder):
            raise NotADirectoryError(test_folder + " is not a directory")
        if not os.path.exists('run'):
            os.mkdir('run')
        os.chdir('run')
        if not os.path.exists(container_name):
            os.mkdir(container_name)
        os.chdir(container_name)
        if os.path.isabs(code_folder):
            self.__system(f'cp -r "{code_folder}" code')
        else:
            self.__system(f'cp -r ../../{code_folder} code')
        if os.path.isabs(test_folder):
            self.__system(f'cp -r "{test_folder}" test')
        else:
            self.__system(f'cp -r ../../{test_folder} test')
        self.status = 'UNKNOWN'

    def compile(self, compile_cmd):
        self.status = 'UNKNOWN'
        self.compiled = True
        # 直接在主机上编译（可选），或在docker内编译
        exit_code = self.__system(f'docker run --rm -v $PWD/code:/code {self.image_name} bash -c "cd /code && {compile_cmd}"')
        if exit_code != 0:
            self.status = 'COMPILE ERROR'
            return 1
        return 0

    def run(self, command, test, time_limit='1000', memory_limit='256m', diff=difflib.diff_default, problem_id='0'):
        try:
            return self.__run(command, test, time_limit, memory_limit, diff, problem_id)
        except Exception as e:
            raise

    def remove(self, delete_testcase=True, delete_code=True):
        if delete_testcase:
            self.__system("rm -rf test")
        if delete_code:
            self.__system("rm -rf code")
        os.chdir('../..')

    def __log(self, level, info):
        if level != 'Debug' and level != 'System' and not self.silence:
            print(f'[{level}] {info}')
        with open('log.txt', 'a') as f:
            f.write(f'[{level}] {info}\n')

    def __system(self, s, check_exit_code=True):
        self.__log('System', s)
        exit_code = os.system(s)
        if exit_code != 0:
            self.__log('System', f'exit_code = {exit_code}')
            if check_exit_code:
                raise SystemError(f'Command Failed : {s}')
        return exit_code

    def __run(self, command, test, time_limit, memory_limit, diff, problem_id):
        # 只用docker的资源限制，不做高频监控
        if self.status == 'COMPILE ERROR':
            return self.status
        # 组装docker命令
        time_limit_sec = int(time_limit) / 1000
        docker_cmd = (
            f'docker run --rm --cpus=1 --memory={memory_limit} --memory-swap={memory_limit} '
            f'-v $PWD/code:/code -v $PWD/test:/test {self.image_name} '
            f'bash -c "cd /code && timeout {time_limit_sec}s {command} < /test/{test}.in > /test/{test}.out 2>> /code/log.txt"'
        )
        self.__log("Debug", f"即将执行docker命令: {docker_cmd}")
        start = time.time()
        docker_cmd_full = docker_cmd + ' > run_log.txt 2>&1'
        exit_code = os.system(docker_cmd_full)
        elapsed = int((time.time() - start) * 1000)
        self.time_ms = elapsed
        self.memory_precent = None  # 无法精确获得
        self.__log("Debug", f"docker命令退出码: {exit_code}")
        # 退出码判断
        if exit_code == 31744 or exit_code == 124:  # timeout
            self.status = 'TIME LIMIT EXECEED'
        elif exit_code == 137:  # OOM killed
            self.status = 'MEMORY LIMIT EXECEED'
        elif exit_code != 0:
            self.status = 'RUNTIME ERROR'
        else:
            # 比对输出
            if problem_id == '584A':
                if difflib._584A(f'test/{test}.out', f'test/{test}.ans', f'test/{test}.in'):
                    self.status = 'WRONG ANSWER'
                else:
                    self.status = 'ACCEPT'
            else:
                if diff(f'test/{test}.out', f'test/{test}.ans'):
                    self.status = 'WRONG ANSWER'
                else:
                    self.status = 'ACCEPT'
        self.__log('Result', self.status)
        # 新增命令行输出
        print(f'[Judge] Test {test}: {self.status} | Time: {self.time_ms} ms')
        return self.status 