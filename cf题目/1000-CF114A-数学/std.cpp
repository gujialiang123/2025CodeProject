#include<bits/stdc++.h>
using namespace std;
long long a,b,n;
bool ans=0;
int main()
{
    cin>>a>>b;//����
    while(b>0)//
    {
        if(b==1)//1��ֱ���ˣ���Ϊb>=2������˵���ɹ��ˣ�
        {
            ans=0;//��ʵû����
            break;
        }
        if(b%a!=0)//mod��������
        {
            ans=1;
            break;
        }
        n++;//ȥ��λ��
        b=b/a;//b��a
    }
    if(ans==0)//YES
    {
        cout<<"YES"<<endl;
        cout<<n-1<<endl;//һ��Ҫ-1
    }
    else//NO
    cout<<"NO"<<endl;
    return 0;
}
