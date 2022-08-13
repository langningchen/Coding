#include<iostream>
#include<algorithm>
#define N ______
using namespace std;
int n,m,q[N],s[N];
int main(){
	cin>>n>>m;
	for(int i=____;i<=___;i++) cin>>q[i];
	s[0]=0;
	for(int i=1;i<=n;i++) s[i]=_______;
	int ans=s[m];
	for(int i=____;i<=n;i++)
		ans=max(ans,s[____]-s[_____]);
	cout<<ans<<endl;	
	return 0;
}
	
	
