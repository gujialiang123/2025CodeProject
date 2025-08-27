#include <bits/stdc++.h>
#define ll long long
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
int q;
map<ll, int> mp, t;
int main(){
    scanf("%d", &q), mp[0] = 1;
    L(i, 1, q){
        char op; ll x; scanf(" %c%lld", &op, &x);
        if(op == '+') mp[x] = 1;
        else{
            int now = t[x];
            while(mp[now * x]) now++;
            printf("%lld\n", now * x), t[x] = now;
        }
    }
    return 0;
}