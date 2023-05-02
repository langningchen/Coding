#include<iostream>
#define N 2009
#define M 509
using namespace std;
int n,m,f[N],w[M],x[M];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>w[i];
	f[0]=0;
	for(int j=1;j<=n;j++){
		f[j]=0;
		for(int i=1;i<=m;i++)
			if(j>=w[i]) 
				f[j]=max(f[j],f[j-w[i]]+w[i]);
	}
	cout<<f[n]<<endl;	
	return 0;
}



