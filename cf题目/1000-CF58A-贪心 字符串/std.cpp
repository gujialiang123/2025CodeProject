#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
char ch[110];
queue<char> que;//建队
int main() {
    que.push('h');
    que.push('e');
    que.push('l');
    que.push('l');
    que.push('o');//将子序列放入队列
    scanf("%s", ch);//读入序列
    int len=strlen(ch);//获得序列长度
    for(int i=0; i<len; i++)//扫描序列
    if(ch[i]==que.front()) que.pop();//如果此时序列元素为队首元素，则弹出队首元素
    if(que.empty()) printf("YES");//如果队列为空，输出"YES"
    else printf("NO");//否则输出"NO"
    return 0;
}
