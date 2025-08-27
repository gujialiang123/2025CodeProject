import requests
import os

class LLMClient:
    def __init__(self, backend="ollama", api_base=None, api_key=None):
        self.backend = backend
        self.api_base = api_base or os.getenv("LLM_API_BASE")
        self.api_key = api_key or os.getenv("LLM_API_KEY")

    def generate(self, prompt, model, **kwargs):
        if self.backend == "ollama":
            return self._generate_ollama(prompt, model, **kwargs)
        elif self.backend == "openai":
            return self._generate_openai(prompt, model, **kwargs)
        elif self.backend == "fastchat":
            return self._generate_fastchat(prompt, model, **kwargs)
        elif self.backend == "vllm":
            return self._generate_vllm(prompt, model, **kwargs)
        else:
            raise ValueError(f"Unknown backend: {self.backend}")

    def _generate_ollama(self, prompt, model, **kwargs):
        url = self.api_base or "http://localhost:11434/api/generate"
        data = {
            "model": model,
            "prompt": prompt,
            "stream": False
        }
        data.update(kwargs)
        resp = requests.post(url, json=data)
        resp.raise_for_status()
        return resp.json().get("response", "")

    def _generate_openai(self, prompt, model, **kwargs):
        url = self.api_base or "https://api.openai.com/v1/chat/completions"
        headers = {
            "Authorization": f"Bearer {self.api_key}",
            "Content-Type": "application/json"
        }
        data = {
            "model": model,
            "messages": [{"role": "user", "content": prompt}],
            "stream": False
        }
        data.update(kwargs)
        resp = requests.post(url, headers=headers, json=data)
        resp.raise_for_status()
        return resp.json()["choices"][0]["message"]["content"]

    def _generate_fastchat(self, prompt, model, **kwargs):
        url = self.api_base or "http://localhost:8000/v1/chat/completions"
        headers = {
            "Authorization": f"Bearer {self.api_key}" if self.api_key else "",
            "Content-Type": "application/json"
        }
        data = {
            "model": model,
            "messages": [{"role": "user", "content": prompt}],
            "stream": False
        }
        data.update(kwargs)
        resp = requests.post(url, headers=headers, json=data)
        resp.raise_for_status()
        return resp.json()["choices"][0]["message"]["content"]

    def _generate_vllm(self, prompt, model, **kwargs):
        url = self.api_base or "http://localhost:8000/v1/chat/completions"
        headers = {
            "Authorization": f"Bearer {self.api_key}" if self.api_key else "",
            "Content-Type": "application/json"
        }
        data = {
            "model": model,
            "messages": [{"role": "user", "content": prompt}],
            "stream": False
        }
        data.update(kwargs)
        resp = requests.post(url, headers=headers, json=data)
        resp.raise_for_status()
        return resp.json()["choices"][0]["message"]["content"] 