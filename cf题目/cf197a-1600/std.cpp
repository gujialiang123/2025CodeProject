#include<cstdio>
using namespace std;
int main(){
	int a,b,r;
	scanf("%d%d%d",&a,&b,&r);
	if(a<r*2||b<r*2)printf("Second");
	else printf("First");
	return 0;
}