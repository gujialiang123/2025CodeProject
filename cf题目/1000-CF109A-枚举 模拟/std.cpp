#include<bits/stdc++.h>//����ͷ�ļ���
using namespace std;
#define ll long long//����ϰ��
int main(){
	ll n,i=0,j=0;
	//�ȶ���ã�i��4�ĸ�����j��7�ĸ�����һ��Ҫ��ʼ��Ϊ0
	scanf("%lld",&n);//����
	i=n/4;n-=i*4;//ǰ�ĵĵ�һ��
	if(n){
		while(i>0){
			n+=4;i--;
			if(n%7==0){j=n/7;n=0;break;}
			//ǰ�ĵĵڶ���
		}
	}
	if(n)printf("-1\n");
	//������ʣ��ģ����޷��������������-1
	else{//����
		while(i>=7){i-=7;j+=4;}//ǰ�ĵĵ�����
		while(i--)printf("4");//���4
		while(j--)printf("7");//���7
		printf("\n");//�����Ǹ���ϰ��
	}
	return 0;//over~
}
