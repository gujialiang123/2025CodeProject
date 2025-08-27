#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n=read(),k=read(),a[100001],f[100001],tip[100001],ans;
signed main(){
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++) f[i]=f[i-1]+a[i];
	for (int i=1;i<=n;i++){
		int l=1,r=i;
		while (l<r){
			int mid=(l+r)/2;
			if (a[i]*(i-mid+1)-f[i]+f[mid-1]<=k) r=mid;
			else l=mid+1;
		}
		tip[i]=i-l+1;
		if (tip[i]>tip[ans]) ans=i;
	}
	cout<<tip[ans]<<' '<<a[ans];
	return 0;
}