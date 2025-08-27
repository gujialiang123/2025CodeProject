#!/usr/bin/env bash
set -euo pipefail

# 直接明文参数（按需修改）
python main.py \
  --problems_path problems \
  --test_path test \
  --backend openai \
  --api_key sk-your-api-key\
  --api_base https://api.302.ai/v1/chat/completions \
  --see_data \
  --query_depth 5 \
  --test_num 5 \
  --output_dir llama3_70B_results_depth5_nums5 \
  --model llama3.3-70b