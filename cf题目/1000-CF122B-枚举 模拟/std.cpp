#include <iostream>
using namespace std;
char c;
int four,seven; //ȫ�ֱ����Զ���ʼ��Ϊ0
int main(){
	while(cin>>c){ //��������һ���ַ�ֱ��������
		if(c=='4') four++;
		else if(c=='7') seven++;
	}
	if(seven==0&&four==0) cout<<-1;
	else if(four>=seven&&four!=0)	cout<<4; //�ر�ע�������Ǵ��ڵ���
	else if(seven>four&&seven!=0) cout<<7;
	return 0;
}
