import sys
import json

try:
    import verl  # type: ignore
except Exception:
    verl = None

from rl.envs.algorithm_env import AlgorithmSolveEnv


def get_default_config(model_name: str = 'llama3-8b', tp: int = 1) -> dict:
    """
    返回示例配置：8B 默认单卡/小并行；切换 70B 时修改 model 与并行参数。
    说明：此配置仅作示意，实际字段以 VERL 版本为准。
    """
    return {
        'model': {
            'name': model_name,          # e.g. 'llama3-8b', 'llama3-70b'
            'dtype': 'bf16',
            'policy_backend': 'hf',      # or 'megatron', etc.
            'tp': tp,                    # tensor parallel size
            'lora': {
                'enable': True,
                'r': 16,
                'alpha': 32,
                'dropout': 0.05
            }
        },
        'rollout': {
            'num_workers': 1,
            'max_rounds': 3,
            'see_data': True
        },
        'train': {
            'algo': 'ppo',               # or grpo/dapo
            'lr': 5e-6,
            'batch_size': 8,
            'micro_batch': 1,
            'epochs': 1
        }
    }


def main():
    if verl is None:
        print('[INFO] VERL 未安装。此脚本为骨架示例。')
        print('[下一步建议] 安装并使用 VERL 后：')
        print(' - 按 get_default_config() 生成/修改训练配置（8B/70B 只需改 model.name 与并行参数）。')
        print(' - 将 AlgorithmSolveEnv 作为 rollout 环境对接到 VERL 的 trainer。')
        cfg = get_default_config('llama3-8b', tp=1)
        print('[示例配置]\n' + json.dumps(cfg, ensure_ascii=False, indent=2))
        return

    # 伪代码：真实使用请参考 VERL 官方 API
    # from verl.trainer import Trainer
    # cfg = get_default_config('llama3-8b', tp=1)
    # env_fn = lambda: AlgorithmSolveEnv(see_data=cfg['rollout']['see_data'],
    #                                    max_rounds=cfg['rollout']['max_rounds'],
    #                                    language='python')
    # trainer = Trainer(config=cfg, env_fn=env_fn)
    # trainer.fit()

    print('[INFO] 已检测到 VERL，可在此处实例化 Trainer 并开始训练。')


if __name__ == '__main__':
    main()
