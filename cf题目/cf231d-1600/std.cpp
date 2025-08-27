#include<bits/stdc++.h>
using namespace std;
struct p
{
	int x , y , z;
}s , t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7;
int ans , a , b , c , d , e , f;
int main()
{
	freopen("cf231D1.in","r",stdout);
	freopen("cf231D1.out","w",stdout);
    //ios::sync_with_stdio(0);
    //ios_base::sync_with_stdio(0);
    cin >> s.x >> s.y >> s.z >> t7.x >> t7.y >> t7.z >> a >> b >> c >> d >> e >> f;
	t0.x = t0.y = t0.z = t1.x = t1.y = t2.y = t2.z = t3.y = t4.x = t4.z = t5.x = t6.z = 0;
	t2.x = t3.x = t6.x = t7.x;
	t4.y = t5.y = t6.y = t7.y;
	t1.z = t3.z = t5.z = t7.z;
	if(s.y < t0.y)
	{
		ans += a;
	}
	if(s.y > t4.y)
	{
		ans += b;
	}
	if(s.z < t2.z)
	{
		ans += c;
	}
	if(s.z > t7.z)
	{
		ans += d;
	}
	if(s.x < t1.x)
	{
		ans += e;
	}
	if(s.x > t6.x)
	{
		ans += f;
	}
	cout << ans << endl;
    return 0;
}
