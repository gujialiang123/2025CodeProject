#include<bits/stdc++.h>
using namespace std;
int n,cnt=0,a[50],ans[10][10],f[50];
void dfs(int x,int y){
	if (x==sqrt(n) and y==sqrt(n)+1){ //�ж��Ƿ��������� 
		cout<<cnt<<endl;//���� 
		for (int i=1;i<=sqrt(n);i++){
			for (int j=1;j<=sqrt(n);j++){
				cout<<ans[i][j]<<" ";
			}
			cout<<endl;
		}
		exit(0);
	}
	if (y>sqrt(n)){//�߽� 
		dfs(x+1,1);
		return ; 
	}
	for (int i=1;i<=n;i++){//ö�ٵ�ǰλ�õ����� 
		if (f[i]!=0) continue; //����Ƿ��ظ�ʹ������ 
		if (y==sqrt(n)){//�жϵ�ǰ�е����ֵĺ��Ƿ�Ϸ� 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[x][j];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n)){//�жϵ�ǰ�е����ֵĺ��Ƿ�Ϸ� 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][y];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n) and y==1){//�жϵ�ǰ�Խ��ߵ����ֵĺ��Ƿ�Ϸ� 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][int(sqrt(n))-j+1];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n) and y==sqrt(n)){//�жϵ�ǰ�Խ��ߵ����ֵĺ��Ƿ�Ϸ� 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][j];
			}
			if (sum!=cnt) continue;
		}
		ans[x][y]=a[i];
		f[i]=1;//��� 
		dfs(x,y+1);
		f[i]=0;
	}
}
int main(){
	cin>>n;
	n=n*n;
	for (int i=1;i<=n;i++){
		cin>>a[i];//���� 
		cnt+=a[i];
	}
	cnt=cnt/sqrt(n);//����Ϸ��ĺ͵�ֵ 
	dfs(1,1);//���� 
	return 0;
}
