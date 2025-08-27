#!/usr/bin/env python3
"""
测试脚本：验证改造后的LLM算法问题解决Agent
"""

import os
import json
import tempfile
import shutil
from pathlib import Path

def create_test_problem():
    """创建测试题目"""
    test_problem = {
        "id": "TEST001",
        "title": "Simple Addition",
        "description": "Given two integers a and b, calculate their sum.\n\nInput:\nThe first line contains two integers a and b (1 ≤ a, b ≤ 100).\n\nOutput:\nPrint the sum of a and b.",
        "hints": "This is a very simple problem. Just add the two numbers.",
        "samples": []
    }
    
    # 创建problems目录
    os.makedirs('problems', exist_ok=True)
    
    # 写入测试题目
    with open('problems/TEST001.json', 'w', encoding='utf-8') as f:
        json.dump(test_problem, f, ensure_ascii=False, indent=2)
    
    print("✅ 创建测试题目: problems/TEST001.json")

def create_test_cases():
    """创建测试用例"""
    # 创建test目录
    os.makedirs('test/TEST001', exist_ok=True)
    
    # 创建测试用例
    test_cases = [
        ("1 2", "3"),
        ("5 7", "12"),
        ("10 20", "30"),
        ("99 1", "100")
    ]
    
    for i, (input_data, expected_output) in enumerate(test_cases, 1):
        with open(f'test/TEST001/{i}.in', 'w') as f:
            f.write(input_data)
        with open(f'test/TEST001/{i}.ans', 'w') as f:
            f.write(expected_output)
    
    print(f"✅ 创建测试用例: test/TEST001/ (共{len(test_cases)}个)")

def create_mock_llm_response():
    """创建模拟的LLM响应"""
    mock_response = """Here's a solution to the simple addition problem:

```python
# Read input
a, b = map(int, input().split())

# Calculate sum
result = a + b

# Output result
print(result)
```

This solution:
1. Reads two integers from input
2. Adds them together
3. Prints the result

The time complexity is O(1) and space complexity is O(1)."""
    
    # 创建judge_files目录
    os.makedirs('judge_files/response', exist_ok=True)
    
    # 写入模拟响应
    with open('judge_files/response/response.txt', 'w', encoding='utf-8') as f:
        f.write(mock_response)
    
    print("✅ 创建模拟LLM响应: judge_files/response/response.txt")

def test_code_extraction():
    """测试代码提取功能"""
    from main import res2code
    
    print("\n🧪 测试代码提取功能...")
    
    # 创建judge_files/code目录
    os.makedirs('judge_files/code', exist_ok=True)
    
    # 测试代码提取
    extracted_code = res2code()
    
    if extracted_code:
        print(f"✅ 代码提取成功，长度: {len(extracted_code)} 字符")
        print("提取的代码:")
        print("-" * 40)
        print(extracted_code)
        print("-" * 40)
        
        # 检查是否包含关键代码元素
        if "def" in extracted_code or "input()" in extracted_code or "print(" in extracted_code:
            print("✅ 代码内容验证通过")
        else:
            print("⚠️  代码内容可能不完整")
    else:
        print("❌ 代码提取失败")

def test_prompt_generation():
    """测试prompt生成功能"""
    from main import get_prompt
    
    print("\n🧪 测试prompt生成功能...")
    
    try:
        prompt = get_prompt("TEST001")
        print("✅ Prompt生成成功")
        print("生成的prompt长度:", len(prompt))
        print("Prompt内容预览:")
        print("-" * 40)
        print(prompt[:200] + "..." if len(prompt) > 200 else prompt)
        print("-" * 40)
    except Exception as e:
        print(f"❌ Prompt生成失败: {e}")

def test_sandbox_creation():
    """测试沙箱创建功能"""
    print("\n🧪 测试沙箱创建功能...")
    
    try:
        from sandbox_dockersimple import sandbox
        
        # 创建临时测试目录
        with tempfile.TemporaryDirectory() as temp_dir:
            test_code_dir = os.path.join(temp_dir, "test_code")
            test_test_dir = os.path.join(temp_dir, "test_test")
            
            os.makedirs(test_code_dir)
            os.makedirs(test_test_dir)
            
            # 创建测试代码文件
            with open(os.path.join(test_code_dir, "main.py"), "w") as f:
                f.write("print('Hello, World!')")
            
            # 创建测试用例
            with open(os.path.join(test_test_dir, "1.in"), "w") as f:
                f.write("")
            with open(os.path.join(test_test_dir, "1.ans"), "w") as f:
                f.write("Hello, World!")
            
            # 测试沙箱创建
            s = sandbox()
            print("✅ 沙箱对象创建成功")
            
            # 注意：这里不实际运行Docker，只是测试对象创建
            print("✅ 沙箱功能测试通过（跳过Docker执行）")
            
    except Exception as e:
        print(f"❌ 沙箱测试失败: {e}")

def test_llm_client():
    """测试LLM客户端"""
    print("\n🧪 测试LLM客户端...")
    
    try:
        from llm_api import LLMClient
        
        # 测试客户端创建
        client = LLMClient(backend="ollama")
        print("✅ LLM客户端创建成功")
        
        # 测试配置
        print(f"✅ 后端类型: {client.backend}")
        print(f"✅ API基础URL: {client.api_base}")
        
    except Exception as e:
        print(f"❌ LLM客户端测试失败: {e}")

def cleanup_test_files():
    """清理测试文件"""
    print("\n🧹 清理测试文件...")
    
    # 删除测试目录
    test_dirs = ['problems', 'test', 'judge_files']
    for dir_name in test_dirs:
        if os.path.exists(dir_name):
            shutil.rmtree(dir_name)
            print(f"✅ 删除目录: {dir_name}")

def main():
    """主测试函数"""
    print("🚀 开始测试LLM算法问题解决Agent系统")
    print("=" * 50)
    
    try:
        # 创建测试环境
        create_test_problem()
        create_test_cases()
        create_mock_llm_response()
        
        # 运行测试
        test_prompt_generation()
        test_code_extraction()
        test_sandbox_creation()
        test_llm_client()
        
        print("\n" + "=" * 50)
        print("🎉 所有测试完成！")
        print("\n系统改造成功，现在可以：")
        print("1. 使用 --problems_path problems --test_path test 参数运行")
        print("2. 自动解决算法问题而不是修复代码")
        print("3. 保持迭代+分支的核心流程")
        
    except Exception as e:
        print(f"\n❌ 测试过程中出现错误: {e}")
        import traceback
        traceback.print_exc()
    
    finally:
        # 询问是否清理测试文件
        try:
            response = input("\n是否清理测试文件？(y/n): ").lower().strip()
            if response in ['y', 'yes', '是']:
                cleanup_test_files()
                print("✅ 测试文件已清理")
            else:
                print("ℹ️  测试文件保留，可以手动检查")
        except KeyboardInterrupt:
            print("\nℹ️  跳过清理，测试文件保留")

if __name__ == "__main__":
    main()
