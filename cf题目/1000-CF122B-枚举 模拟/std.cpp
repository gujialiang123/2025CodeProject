#include <iostream>
using namespace std;
char c;
int four,seven; //全局变量自动初始化为0
int main(){
	while(cin>>c){ //持续读入一个字符直到读不到
		if(c=='4') four++;
		else if(c=='7') seven++;
	}
	if(seven==0&&four==0) cout<<-1;
	else if(four>=seven&&four!=0)	cout<<4; //特别注意这里是大于等于
	else if(seven>four&&seven!=0) cout<<7;
	return 0;
}
