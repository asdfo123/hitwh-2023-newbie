#include <bits/stdc++.h>
using namespace std;
int a[50];
int tl[1050];
int main ()
{
    int x,n,m;
    cin>>x>>n>>m;
    int cnt1 = 0,cnt2 = 0;
    int now = 0;
    for(int i = 1;i <= n;i++) 
    {
    	cin>>a[i];
    	tl[a[i]] = 1;
    	if(a[i] <= x) cnt1++;
    	else continue;
    }
    int time = 0;
    int anss = 0;
    for(int i = 1;i <= x;i++)
    {
    	if(tl[i]) time+=30;
    	if(time)
    	{
    		anss++;
    		time--;
    	}
    }
    anss *= 200;
    for(int i = 1;i <= m;i++) 
    {
    	int b;
    	cin>>b;
    	if(b <= x) cnt2++;
    	else continue;
    }
    int ans = cnt2*10;
    int tot1 = 1800*((x+6)/7);
    int tot2 = 200*((x+5)/7);
    int tot3 = 500*((x+4)/7);
    int tot4 = 100*x;
    int tot5 = 6*180*cnt1;
    int tot6 = 42*180*cnt2;
    int tot = tot1+tot2+tot3+tot4+tot5+tot6+anss;
    //cout<<tot<<endl;
    ans = ans + tot/600;
    cout<<ans<<endl;
}