#include<bits/stdc++.h>//����ͷ�ļ�
using namespace std;
string a;//����һ���ַ���
int main(){
    cin>>a;//���룬����˵�˰�
    int la=a.length();//Ϊ�˷���
    for(int i=0;i<la;i++){//�ַ�һ�ɴ�0��ʼ
        if(a[i]>='A'&&a[i]<='Z')
        	a[i]+=32;//��д��ĸתСд��ĸ
        if(a[i]!='a'&&a[i]!='o'&&a[i]!='y'&&a[i]!='e'&&a[i]!='u'&&a[i]!='i')//�����ж�
        	cout<<"."<<a[i];//�Ǹ���ǰ��������.����Ȼ�����ַ�a[i]
    }
    return 0;//��ϰ��
}
