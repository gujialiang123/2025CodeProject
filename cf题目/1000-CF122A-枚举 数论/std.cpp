#include<cstdio>
using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    if(n%4==0||n%7==0||n%74==0||n%47==0||n%44==0||n%77==0)
    //�ܱ���������������77���ϵ����ֲ���Ҫ�ж��ˣ�
        return printf("YES"),0;
    while(n!=0)
    {
        register int t=n%10;
        if(t!=4&&t!=7)  return printf("NO"),0;
        n/=10;
    }
    return printf("YES"),0;
}
