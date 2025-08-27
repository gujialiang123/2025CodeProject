#include<bits/stdc++.h>
using namespace std;
int n,m,tot;
int main(){
    scanf("%d",&n);getchar();
    if (n&1) m=(n-1)/2-1;
    else m=n/2-1;
    for (int i=1;i<=n;i++){
        printf("%c",getchar());
        if (m){tot++;if (tot==2) printf("-"),m--,tot=0;}
    }
    return 0;
}