#include<bits/stdc++.h> 
using namespace std;
int n,m,C[100][100];
int main(){
	freopen("combination.in","r",stdin);
	freopen("combination.out","w",stdout);
	cin>>n>>m;
	for(int i=0;i<=n;i++)C[i][0]=1;
	for(int j=1;j<=n;j++)
		for(int i=j;i<=n;i++)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	for(int i=0;i<=n;i++,cout<<endl)
		for(int j=0;j<=i;j++)cout<<C[i][j]<<" ";
	cout<<C[n][m]<<endl;
	return 0;
}


