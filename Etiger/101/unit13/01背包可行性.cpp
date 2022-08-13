/*姓名XXX
输入n=3,m=7
x[1]=2
x[2]=4
x[3]=3 
f[i][j]表示只用前i个数字能否凑出j
    j=0,j=1,j=2,j=3,j=4,j=5,j=6,j=7
i=0  1   0   0   0   0   0   0   0
i=1  1   0   1   0   0   0   0   0
i=2  1   0   1   0   1   0   1   0
i=3  1   0   1   1   1   1   1   1
*/
#include<bits/stdc++.h>
using namespace std;
const int N=109;
const int M=209;
int n,m,x[N],f[N][M]; 
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>x[i];	
	f[0][0]=1;
	for(int i=1;i<=n;++i)   
		for(int j=0;j<=m;++j) 
			if(j<x[i])  
				f[i][j]=f[i-1][j];
			else 	
				f[i][j]=f[i-1][j] or f[i-1][j-x[i]];
	if(f[n][m])cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
} 


