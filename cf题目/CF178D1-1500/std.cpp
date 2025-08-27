#include<bits/stdc++.h>
using namespace std;
int n,cnt=0,a[50],ans[10][10],f[50];
void dfs(int x,int y){
	if (x==sqrt(n) and y==sqrt(n)+1){ //判断是否可以输出答案 
		cout<<cnt<<endl;//出答案 
		for (int i=1;i<=sqrt(n);i++){
			for (int j=1;j<=sqrt(n);j++){
				cout<<ans[i][j]<<" ";
			}
			cout<<endl;
		}
		exit(0);
	}
	if (y>sqrt(n)){//边界 
		dfs(x+1,1);
		return ; 
	}
	for (int i=1;i<=n;i++){//枚举当前位置的数字 
		if (f[i]!=0) continue; //标记是否重复使用数字 
		if (y==sqrt(n)){//判断当前行的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[x][j];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n)){//判断当前列的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][y];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n) and y==1){//判断当前对角线的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][int(sqrt(n))-j+1];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n) and y==sqrt(n)){//判断当前对角线的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][j];
			}
			if (sum!=cnt) continue;
		}
		ans[x][y]=a[i];
		f[i]=1;//标记 
		dfs(x,y+1);
		f[i]=0;
	}
}
int main(){
	cin>>n;
	n=n*n;
	for (int i=1;i<=n;i++){
		cin>>a[i];//输入 
		cnt+=a[i];
	}
	cnt=cnt/sqrt(n);//求出合法的和的值 
	dfs(1,1);//搜索 
	return 0;
}
