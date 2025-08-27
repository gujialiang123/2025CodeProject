import os
import json
from typing import Callable, List, Dict, Any

from rl.envs.algorithm_env import AlgorithmSolveEnv


def default_policy(observation: Dict[str, Any]) -> str:
    """占位策略：返回一个简单的代码，实际训练时应替换为LLM输出。"""
    # 极简占位：读取一行、原样输出（很多题会WA，仅用于流程验证）
    return "print(input())\n"


def collect_dataset(problem_ids: List[str],
                    out_path: str = 'rlhf_dataset.jsonl',
                    max_rounds: int = 3,
                    see_data: bool = True,
                    language: str = 'python',
                    policy_fn: Callable[[Dict[str, Any]], str] = default_policy) -> None:
    env = AlgorithmSolveEnv(see_data=see_data, max_rounds=max_rounds, language=language)
    with open(out_path, 'w', encoding='utf-8') as fout:
        for pid in problem_ids:
            obs = env.reset(pid)
            episode = []
            done = False
            while not done:
                # 这里应由策略（如LLM）根据obs生成代码
                action_code = policy_fn(obs)
                next_obs, reward, done, info = env.step(action_code)
                record = {
                    'problem_id': pid,
                    'round': obs['round'],
                    'prompt': obs.get('description', ''),
                    'hints': obs.get('hints', ''),
                    'response': action_code,
                    'feedback': next_obs.get('feedback', ''),
                    'reward': reward,
                    'status': info.get('status')
                }
                fout.write(json.dumps(record, ensure_ascii=False) + '\n')
                obs = next_obs
            env.close()


if __name__ == '__main__':
    # 示例：采集少量数据（请替换为你的问题集与真实策略）
    sample_problems = ['1A', '102B']
    collect_dataset(sample_problems, out_path='rlhf_dataset.jsonl', max_rounds=2)
