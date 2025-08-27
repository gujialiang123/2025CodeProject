#include<iostream>
using namespace std;

int n,a[100010],s[100010];//s为记录前缀和的数组

int ans;//记录答案

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }//读入+统计前缀和
    for(int i=1;i<=n-1;i++){
        if(s[i]==s[n]-s[i])//比较两个区间的和是否一样
            ans++;//如果一样，答案++
    }
    cout<<ans<<endl;//输出答案
    return 0;//完结撒花！
}