/*
f[i]记录能否正好走到第i级
输入样例n=10,a=3,b=4
   i=0,1,2,3,4,5,6,7,8,9,10
f[i]=1,0,0,1,1,0,1,1,1,1,1
*/
#include<iostream>
using namespace std;
bool f[100];
int n,a,b;
int main(){
	cin>>n>>a>>b;
	f[0]=1; 
	for(int i=1;i<=n;i++){
		f[i]=0;
		if(i>=a) f[i]=(f[i] or f[i-a]);
		if(i>=b) f[i]=(f[i] or f[i-b]);
	}
	for(int i=0;i<=n;i++)
		cout<<i<<":"<<f[i]<<endl;
	return 0;
}


