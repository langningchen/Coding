#include<iostream>
using namespace std;
const int N=1009;
int a[N],n,bigi;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	bigi=1;
	for(int i=2;i<=n;i++)
		if(a[i]>a[bigi])
			bigi=i;
	cout<<bigi<<endl;
	return 0;
}
