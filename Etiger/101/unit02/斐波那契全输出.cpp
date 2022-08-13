#include<iostream>
using namespace std;
unsigned long long n,f[100];
int main(){
	cin>>n;
	f[1]=1; 
	f[2]=2; 
	for(int i=3;i<=n;i++)
		f[i]=f[i-1]+f[i-2];
	for(int i=1;i<=n;i++)
		cout<<i<<": "<<f[i]<<endl;
	return 0;
}


