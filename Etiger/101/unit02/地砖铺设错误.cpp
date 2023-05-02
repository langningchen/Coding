#include<bits/stdc++.h>
using namespace std;
const int N=100009;
const int MOD=1000007;
long long n,f[N];
int main(){
	cin>>n;
	f[1]=1; 
	f[2]=2; 
	for(int i=3;i<=n;i++)
		f[i]=f[i-1]+f[i-2];
	cout<<f[n]%MOD<<endl;
	return 0;
}


