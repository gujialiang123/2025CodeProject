#include <iostream>
#include <string>
using namespace std;
string f[11] = {"ABSINTH","BEER","BRANDY","CHAMPAGNE","GIN","RUM","SAKE","TEQUILA","VODKA","WHISKEY","WINE"};//���־� 
int main()
{
	int n,ans = 0;
	string str;
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>str;
		if(str[0] >= '0' && str[0] <= '9')//���������� 
		{
			if(str.size() == 1) ans++;//����Ϊ��λ��
			else if(str[0] == '1' && str[1] <='7' && str.size() == 2) ans++;//С��18��� 
		}
		else //���������� 
		{
			for(int j = 0;j <= 10;j++)
				if(str == f[j]) ans++;//�����Ǿ� 
		} 	 
	}
	cout<<ans<<endl;
	return 0;
} 
