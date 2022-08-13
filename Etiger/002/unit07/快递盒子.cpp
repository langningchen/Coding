#include<iostream>
using namespace std;
int n,x,a[101];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>x;
	for(int i=1;i<=n;i++)
		if(a[i]%x==0)
			cout<<i<<" ";
	return 0;
}


