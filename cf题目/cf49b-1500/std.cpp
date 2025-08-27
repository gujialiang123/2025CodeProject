#include <bits/stdc++.h>
using namespace std;
#define R register int
const int MAXN = 1e3 + 10;
int a[MAXN], b[MAXN], c[MAXN];
int main() {
    int x, y; scanf("%d%d", &x, &y);
    int cnt = 0, tot = 0, p = -1;
    while (x) {
        a[++ cnt] = x % 10;
        x /= 10; p = max(p, a[cnt]);
    }
    while(y) {
        b[++ tot] = y % 10;
        y /= 10; p = max(p, b[tot]);
    }
    int ans = max(tot, cnt);
    for(R i = 1; i <= ans; i ++) {
        c[i] += a[i] + b[i];
        if(c[i] > p) c[i + 1] ++;
    }
    if(c[ans + 1]) ans ++;
    printf("%d\n", ans);
    return 0;
}
