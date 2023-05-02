#include<iostream>
using namespace std;
int n,f[1009];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>f[i];
	int j=1;
	for(int i=2;i<=n;i++)
		if(f[i]>f[j])
			j=i;
	cout<<f[j]<<endl;
	return 0;
}


