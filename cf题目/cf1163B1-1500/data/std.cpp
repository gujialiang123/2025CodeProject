#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 998244353 //����һ��MOD

signed main()
{
	int n;
	int ans = 0;
	string s;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		int t = 0, len = s.length();
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				t = t * 10 + s[i] - '0'; //����ǰ����˵�Ĳ���
				t %= MOD; //���һ��Ҫ�ǵ�ģһ��
			}
		}
		ans += t;
		ans %= MOD; //���ҲҪģһ��
	}
	ans *= n;
	ans %= MOD;
	cout << ans << endl;
	return 0; //�������~
}

