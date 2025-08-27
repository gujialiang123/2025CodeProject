#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, y = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        y = (c == '-') ? -1 : 1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x * y;
}
int l[5005], r[5005], s = 0, sum[5005];
int n;
vector<int> ans; // vector
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        l[i] = read(), r[i] = read(), sum[i] = 0;
    }
    for (int i = 1; i <= n; i++) //要双重循环
        for (int j = 1; j < i; j++)
        {
            if (l[i] < r[j] && l[j] < r[i]) //判断是否要取消
            {
                sum[i]++;
                sum[j]++;
                s++;
            }
        }
    for (int i = 1; i <= n; i++)
        if (sum[i] == s)
            ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}