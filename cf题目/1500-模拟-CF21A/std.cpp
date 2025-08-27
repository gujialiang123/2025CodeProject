#include<iostream>
#include<string>
using namespace std;
bool checkone(string str)//检查username
{
	if(str.size()>=17||str.size()==1)return 0;//长度判断，这里str.size()==1判断了是不是空的
	for(int p=0;p<str.size();p++)
		if(str[p]!='@')
			if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;//如果不合法，直接返回 
	return 1;//不然就是合法的
}
bool checktwo(string str)//检查hostname
{
	int sum=0;
	if(str[0]=='.')return 0;//特判如果第一个字符是.
	if(str.size()==0)return 0;//如果是空的
	if(str.size()>=33|| (str.size()==1&&str[0]=='/'))return 0;//特判长度
	for(int p=0;p<str.size();p++)//然后是挨个判断
	{
		if(str[p]=='.'&&str[p+1]=='.')//有相邻的.
			return 0;
		if(str[p]!='.')
			if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
	}
	return 1;
}
bool checkthree(string str)//检查resource
{
	if(str[0]=='/'&&str.size()==1)return 0; //特判只有/的情况
	for(int p=0;p<str.size();p++)//挨个判断
		if(str[p]!='/')
			if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
	return 1;//返回
}
int main()
{
	string str;
	getline(cin,str);
	if(str.find('@')==string::npos)//如果连@都没有，肯定直接输出
	{
		cout<<"NO"<<endl;
		return 0;
	}
	string so1=str.substr(0,str.find('@')+1);//username字段
	string so2=str.substr(str.find('@')+1,str.find('/')-str.find('@')-1);//hostname字段
	string so3=((str.find('/')!=string::npos)?(str.substr(str.find('/'),str.size()-str.find('/'))):(""));//resource
	if(checkone(so1)&&checktwo(so2)&&checkthree(so3)&&str[str.size()-1]!='.'&&so1.size()+so2.size()+so3.size()==str.size())//最后一个字符不能是.
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
}