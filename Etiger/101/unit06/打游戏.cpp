/*
f[i]代表什么含义 
输入样例：... 
   i=0,1,2,3,...
f[i]=0,... 
*/
#include<iostream>
using namespace std;
int n,f[109],x[109];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i];
	f[0]=0; 
	f[1]=x[1]; 
	for(i=2;i<=n;i++)
		f[i]=max(f[i-1],f[i-2]+x[i]);
	cout<<f[n]<<endl;
	return 0;
}


