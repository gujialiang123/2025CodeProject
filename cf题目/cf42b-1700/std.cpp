#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int mp[9][9];
char s[2];
int dx[9]={0,0,0,1,-1,1,1,-1,-1};
int dy[9]={0,1,-1,0,0,1,-1,1,-1};
int roots[3][2];
int main(){
	f(i,1,2){//������
		cin>>s;
		roots[i][0]=s[0]-'a'+1;//����ת��������ͬ��
		roots[i][1]=s[1]-'0';
		f(i,1,8){//������Ⱦɫ
			if(i==s[1]-'0')continue;
			mp[s[0]-'a'+1][i]++;
		}
		f(i,1,8){//����ҲȾɫ
			if(i==s[0]-'a'+1)continue;
			mp[i][s[1]-'0']++;
		}
	}
	cin>>s;//�������
	int sx=s[0]-'a'+1,sy=s[1]-'0';
	f(i,1,8){
		if(sx+dx[i]<1||sx+dx[i]>8||sy+dy[i]<1||sy+dy[i]>8)continue;
		mp[sx+dx[i]][sy+dy[i]]++;
	}
	f(j,1,2){//����Ƿ�ס��
		if(roots[j][0]==sx){
			if(roots[j][1]>sy)f(i,1,sy-1)mp[sx][i]--;
			else f(i,sy+1,8)mp[sx][i]--;
		}
		if(roots[j][1]==sy){
			if(roots[j][0]>sx)f(i,1,sx-1)mp[i][sy]--;
			else f(i,sx+1,8)mp[i][sy]--;
		}
	}
	cin>>s;
	sx=s[0]-'a'+1,sy=s[1]-'0';
	f(i,0,8){//��������Χ����
		if(sx+dx[i]<1||sx+dx[i]>8||sy+dy[i]<1||sy+dy[i]>8)continue;
		if(!mp[sx+dx[i]][sy+dy[i]]){
			cout<<"OTHER";//���ߵ�
			return 0;
		}
	}
	cout<<"CHECKMATE";
	return 0;
}
