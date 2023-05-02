#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
const ll MOD=1000000007;
const ll N=1009;
ll n,m,C[N][N];
int main(){
	cin>>n>>m;
	for(ll i=0;i<=n;i++)C[i][0]=1;
	for(ll j=1;j<=n;j++)
		for(ll i=j;i<=n;i++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	cout<<C[n][m]<<endl;
	return 0;
}


