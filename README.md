# LLM Algorithm Problem Solver Agent

这是一个基于大语言模型(LLM)的算法问题自动解决Agent系统，能够自动分析算法问题并生成解决方案。

## 功能特点

### 🔄 **迭代+分支解决流程**
- **初始分析**: LLM分析问题描述，生成初始解决方案
- **代码验证**: 在Docker沙箱中运行代码，通过测试用例验证
- **智能反馈**: 根据判题结果（WA/TLE/RE/MLE）生成针对性改进指导
- **迭代优化**: 多轮改进直到通过所有测试用例

### 🚀 **多后端LLM支持**
- **Ollama**: 本地部署的开源模型（默认）
- **OpenAI**: GPT系列模型
- **FastChat**: 开源聊天模型
- **vLLM**: 高性能推理框架

### 📊 **完整的进度管理**
- 断点续传，支持长时间运行
- 详细的对话记录和解决历史
- 统计分析和结果汇总

## 使用方法

### 1. 命令行模式（推荐）

```bash
# 批量解决所有题目
python main.py --problems_path problems --test_path test --output_dir results --model llama3

# 只解决特定题目
python main.py --problems_path problems --test_path test --problem_filter "1A,102B" --model llama3

# 设置解决轮次和测试次数
python main.py --problems_path problems --test_path test --query_depth 3 --test_num 5 --model llama3

# 使用OpenAI后端
python main.py --problems_path problems --test_path test --backend openai --model gpt-4 --api_key YOUR_API_KEY

# 查看进度
python main.py --problems_path problems --test_path test --show_progress

# 清除进度，重新开始
python main.py --problems_path problems --test_path test --clear_progress
```

### 2. 参数说明

| 参数 | 必需 | 说明 |
|------|------|------|
| `--problems_path` | ✅ | problems目录路径 |
| `--test_path` | ✅ | test目录路径 |
| `--output_dir` | ❌ | 输出目录（默认：results） |
| `--model` | ❌ | 使用的模型名称（默认：llama3） |
| `--test_num` | ❌ | 测试次数（默认：1） |
| `--query_depth` | ❌ | 解决轮次（默认：1） |
| `--see_data` | ❌ | 错误反馈中是否包含测试数据 |
| `--backend` | ❌ | LLM后端（ollama/openai/fastchat/vllm） |
| `--api_key` | ❌ | API密钥（用于openai等） |
| `--problem_filter` | ❌ | 只处理指定题目（如：1A,102B） |

### 3. 目录结构

```
CodeProject/
├── problems/           # 题目描述文件（JSON格式）
│   ├── 1A.json
│   ├── 102B.json
│   └── ...
├── test/              # 测试用例
│   ├── 1A/
│   │   ├── 1.in
│   │   ├── 1.ans
│   │   └── ...
│   └── ...
├── results/           # 输出结果
│   ├── solve_results.jsonl      # 解决结果
│   ├── conversation_logs.jsonl  # 对话记录
│   ├── summary.json            # 统计汇总
│   └── progress.json           # 进度文件
└── main.py           # 主程序
```

## 工作流程

### 1. **问题分析阶段**
```
问题描述 → LLM分析 → 生成初始解决方案
```

### 2. **代码验证阶段**
```
生成代码 → Docker沙箱执行 → 测试用例验证
```

### 3. **迭代改进阶段**
```
判题结果 → 生成改进指导 → LLM优化 → 重新验证
```

### 4. **结果记录阶段**
```
成功/失败状态 → 记录对话历史 → 更新统计信息
```

## 支持的判题结果

- **ACCEPT**: 解决方案正确，通过所有测试
- **WRONG ANSWER (WA)**: 输出结果错误
- **TIME LIMIT EXCEEDED (TLE)**: 超时
- **RUNTIME ERROR (RE)**: 运行时错误
- **MEMORY LIMIT EXCEEDED (MLE)**: 内存超限
- **COMPILE ERROR (CE)**: 编译错误

## 环境要求

### 基础环境
- Python 3.7+
- Docker（用于代码执行沙箱）

### LLM后端
- **Ollama**: 本地部署，无需API密钥
- **OpenAI**: 需要API密钥
- **FastChat**: 本地部署或远程服务
- **vLLM**: 高性能推理服务

## 安装和配置

### 1. 安装依赖
```bash
pip install requests numpy
```

### 2. 配置LLM后端

#### Ollama（推荐用于本地测试）
```bash
# 安装Ollama
curl -fsSL https://ollama.ai/install.sh | sh

# 下载模型
ollama pull llama3
```

#### OpenAI
```bash
export LLM_API_KEY="your-api-key-here"
```

### 3. 准备题目和测试用例

确保`problems/`目录包含题目描述文件，`test/`目录包含对应的测试用例。

## 示例运行

```bash
# 解决题目1A
python main.py --problems_path problems --test_path test --problem_filter "1A" --model llama3 --query_depth 2

# 使用OpenAI解决多个题目
python main.py --problems_path problems --test_path test --problem_filter "1A,102B,136A" --backend openai --model gpt-4 --api_key YOUR_KEY
```

## 输出文件说明

### `solve_results.jsonl`
每行一个JSON对象，记录每次解决的详细信息：
```json
{
  "problem_id": "1A",
  "test_num": 1,
  "query_depth": 2,
  "model_name": "llama3",
  "status": "SUCCESS",
  "pass_count": 1,
  "total_tests": 1,
  "fix_rounds": 2,
  "error_types": ["WRONG ANSWER"],
  "solution_code": "def solve(n, m, a):\n    return ((n + a - 1) // a) * ((m + a - 1) // a)",
  "conversation_id": "1A_1_20241201_143022"
}
```

### `conversation_logs.jsonl`
记录完整的对话过程，包括：
- 初始问题描述
- LLM的解决方案
- 判题结果和错误反馈
- 改进指导

### `summary.json`
统计汇总信息，包括：
- 每个题目的成功率
- 平均解决轮次
- 错误类型分布

## 故障排除

### 常见问题

1. **Docker权限问题**
   ```bash
   sudo usermod -aG docker $USER
   # 重新登录后生效
   ```

2. **LLM连接失败**
   - 检查后端服务是否正常运行
   - 验证API密钥和配置
   - 检查网络连接

3. **内存不足**
   - 减少并发测试数量
   - 使用更小的模型
   - 增加系统内存

### 调试模式

启用详细日志输出：
```bash
python main.py --problems_path problems --test_path test --model llama3 2>&1 | tee debug.log
```

## 扩展和定制

### 添加新的LLM后端
在`llm_api.py`中添加新的后端实现。

### 自定义判题逻辑
修改`sandbox_dockersimple.py`中的判题逻辑。

### 添加新的编程语言支持
扩展代码生成和编译逻辑。

## 强化学习子框架（rl/）

本项目保留现有“评测Agent”（main.py 流程）不变，新增一个独立的 RL 子框架，用于对接 VERL 等强化学习训练或生成 RLHF/RLAIF 数据。

### 目录
- `rl/envs/algorithm_env.py`: 最小可用环境类（reset/step/close）。输入为题目描述，动作为代码字符串，环境用沙箱判题并返回奖励与反馈。
- `rl/judger.py`: 直接对代码字符串进行判题的封装，便于独立调用或并发使用。
- `rl/collect_rlhf_data.py`: 采样脚本，按问题集迭代生成 (prompt, response, reward, feedback) JSONL。

### 环境接口
- `reset(problem_id) -> observation`：返回题目描述、提示等。
- `step(action_code: str) -> (observation, reward, done, info)`：写入代码、沙箱判题，产生奖励与下一轮反馈。
- 奖励默认：ACCEPT=1.0；WA 基于通过比例给 0~0.5；TLE/MLE/RE/CE=-0.2（可按需修改）。

### 采集 RLHF 数据
```bash
python rl/collect_rlhf_data.py
# 生成 rlhf_dataset.jsonl
```

### 与 VERL 对接（思路）
- 在线 RL：将 `AlgorithmSolveEnv` 注册为自定义环境，policy 产生代码字符串，env 判题产出 reward/obs。
- 离线/半在线：用 `rl/judger.py`/`rl/collect_rlhf_data.py` 批量生成 (prompt, response, reward) 样本，喂入 VERL 训练器。

注意：RL 子框架使用独立的临时工作目录与容器名，支持并发；不修改现有评测流程。

## 许可证

本项目采用MIT许可证。

## 贡献

欢迎提交Issue和Pull Request来改进这个项目！
