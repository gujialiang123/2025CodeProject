#include<bits/stdc++.h>//万能头文件
using namespace std;
string a;//定义一个字符串
int main(){
    cin>>a;//输入，不用说了吧
    int la=a.length();//为了方便
    for(int i=0;i<la;i++){//字符一律从0开始
        if(a[i]>='A'&&a[i]<='Z')
        	a[i]+=32;//大写字母转小写字母
        if(a[i]!='a'&&a[i]!='o'&&a[i]!='y'&&a[i]!='e'&&a[i]!='u'&&a[i]!='i')//暴力判断
        	cout<<"."<<a[i];//是辅音前面就输出“.”，然后是字符a[i]
    }
    return 0;//好习惯
}
