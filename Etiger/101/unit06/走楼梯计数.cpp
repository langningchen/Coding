/*
g[i]记录正好走到第i级有几种走法 
输入样例n=10,a=2,b=3
   i=0,1,2,3,4,5,6,7,8,9,10
g[i]=1,0,1,1,1,2,2,3,4,5,7
*/
#include<iostream>
using namespace std;
long long n,a,b,g[100];
int main(){
	cin>>n>>a>>b;
	g[0]=1; 
	for(int i=1;i<=n;i++){
		g[i]=0;
		if(i>=a) g[i]+=g[i-a];
		if(i>=b) g[i]+=g[i-b];
	}
	for(int i=0;i<=n;i++)
		cout<<i<<":"<<g[i]<<endl;
	return 0;
}


