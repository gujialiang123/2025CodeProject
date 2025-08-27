#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 3e6 + 80;
int t, n, p, k, a[N], z[N], ans;

int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);//��������ʱ��
	cin >> t;
	while(t--)
	{
		ans = 0;
		cin >> n >> p >> k;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + n + 1);//��С��������
		for(int i = 1; i <= n; i++)
			z[i] = 0x3f3f3f3f;//����memset,ȫ����ֵ
		for(int i = 1; i <= n; i++)
		{//��������� 
			if(i >= k) z[i] = min(z[i], z[i - k] + a[i]);
			z[i] = min(z[i], z[i - 1] + a[i]);
		}
		for(int i = 1; i <= n; i++)
			if(z[i] <= p) ans = i;//ö�����մ�
		cout << ans << endl;
	}
}
