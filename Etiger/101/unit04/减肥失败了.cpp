#include<iostream>
#include<algorithm>
#define N 1009
using namespace std;
int n,q[N],s[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>q[i];
	s[0]=0;
	for(int i=1;i<=n;i++) s[i]=s[i-1]+q[i];
	int ans=s[7];
	for(int i=8;i<=n;i++)
		ans=max(ans,s[i]-s[i-7]);
	cout<<ans<<endl;	
	return 0;
}
	
	
