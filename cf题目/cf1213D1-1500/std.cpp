#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 55, maxm = 200005;

int A[maxn];  // ԭ����
int cnts[maxm]; // cnts[i]��ʾ��������������i��Ҫ�Ĵ���
int cntc[maxm]; // cntc[i]��ʾ���i������
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    sort(A + 1, A + n + 1); // ��Ҫ��С�������δ���
    for (int i = 1; i <= n; i++) {
        int x = A[i], sum = 0;
        while (x) {
            if (cntc[x] < k) 
                cntc[x]++, cnts[x] += sum;
            // else 
            //  �Ѿ��ﵽk�������ˣ�Ϊ�˱�֤��С���������Բ����в���
            
            x /= 2;
            sum++;
        }
    }
    int ans = -1u / 2; // -1u/2=2^31-1
    for (int i = 1; i <= maxm; i++)
        if (cntc[i] >= k)
            ans = min(ans, cnts[i]); // ��������������������ȡ��������С��
    printf("%d\n", ans);
    return 0;
}
