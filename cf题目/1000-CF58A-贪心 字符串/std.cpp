#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
char ch[110];
queue<char> que;//����
int main() {
    que.push('h');
    que.push('e');
    que.push('l');
    que.push('l');
    que.push('o');//�������з������
    scanf("%s", ch);//��������
    int len=strlen(ch);//������г���
    for(int i=0; i<len; i++)//ɨ������
    if(ch[i]==que.front()) que.pop();//�����ʱ����Ԫ��Ϊ����Ԫ�أ��򵯳�����Ԫ��
    if(que.empty()) printf("YES");//�������Ϊ�գ����"YES"
    else printf("NO");//�������"NO"
    return 0;
}
