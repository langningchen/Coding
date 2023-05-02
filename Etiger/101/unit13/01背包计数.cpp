/*姓名XXX
输入n=4,m=6
x[1]=2
x[2]=5
x[3]=1 
x[4]=3
g[i][j]表示用前i个数字恰好凑出j共几种方案
    j=0,j=1,j=2,j=3,j=4,j=5,j=6
i=0  1   0   0   0   0   0   0  
i=1  1   0   1   0   0   0   0  
i=2  1   0   1   0   0   1   0  
i=3  1   1   1   1   0   1   0  
i=4  1   1   1   2   1   2   2  
*/
#include<bits/stdc++.h>
using namespace std;
const int N=109;
const int M=209;
int n,m,x[N],g[N][M]; 
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>x[i];	
	g[0][0]=1;
	for(int i=1;i<=n;++i)   
		for(int j=0;j<=m;++j) 
			if(j<x[i])  
				g[i][j]=g[i-1][j];
			else 	
				g[i][j]=g[i-1][j] + g[i-1][j-x[i]];
	cout<<g[n][m]<<endl;
	return 0;
} 


