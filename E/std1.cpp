#include <bits/stdc++.h>
using namespace std;
bool prime(int x)
{
	if(x == 0||x == 1) return false;
	for(int i = 2;i <= sqrt(x);i++)
	{
		if(x%i==0) return false;
	}
	return true;
}
int pal[1000000];
int tot = 0;
void pre()
{
	int d1,d2,d3,d4,d5;
	int palindrome;
	for (d1 = 1; d1 <= 9; d1++) { 
    for (d2 = 0; d2 <= 9; d2++) {
         for (d3 = 0; d3 <= 9; d3++) {
         	 for (d4 = 0; d4 <= 9; d4++) {
         	 	 for (d5 = 0; d5 <= 9; d5++) {
           			palindrome = 100000000*d1 + 10000000*d2 +1000000*d3 + 100000*d4 + 10000*d5+ 1000*d4 + 100*d3 + 10*d2 + d1;
           			if(prime(palindrome)) pal[++tot] = palindrome;
         		}
         		palindrome = 10000000*d1 + 1000000*d2 +100000*d3 + 10000*d4+ 1000*d4 + 100*d3 + 10*d2 + d1;
           		if(prime(palindrome)) pal[++tot] = palindrome;
         		palindrome = 1000000*d1 + 100000*d2 +10000*d3 + 1000*d4 + 100*d3 + 10*d2 + d1;
         		if(prime(palindrome)) pal[++tot] = palindrome;
         	}
         	palindrome = 100000*d1 + 10000*d2 +1000*d3 + 100*d3 + 10*d2 + d1;
         	if(prime(palindrome)) pal[++tot] = palindrome;
         	palindrome = 10000*d1 + 1000*d2 +100*d3 + 10*d2 + d1;
         	if(prime(palindrome)) pal[++tot] = palindrome;
         	
         }
         palindrome = 1000*d1 + 100*d2 + 10*d2 + d1;
        if(prime(palindrome)) pal[++tot] = palindrome;
         palindrome = 100*d1 + 10*d2 +d1;
         if(prime(palindrome)) pal[++tot] = palindrome;
         
     }
     palindrome = 10*d1 + d1;
        if(prime(palindrome)) pal[++tot] = palindrome;
     palindrome = d1;
     if(prime(palindrome)) pal[++tot] = palindrome;
 	}
 	sort(pal+1,pal+tot+1);
}
void solve()
{
	int n;
	cin>>n;
	int l = 1,r = tot;
	// for(int i = 1;i <= tot;i++)
	// cout<<pal[i]<<endl;
	int ans = 0;
	while(l <= r)
	{
		int mid = l+r>>1;
		if(pal[mid]>n) r = mid - 1;
		else l = mid+1,ans = mid;
	}
	cout<<ans<<endl;
}
signed main() {
	
	int T;
	cin>>T;
	pre();
	while(T--)
	{
		solve();
	}
}
