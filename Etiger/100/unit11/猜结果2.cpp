#include<iostream>
#include<algorithm>
using namespace std;
const int N=109;
int n,d[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>d[i];
	sort(d+1,d+1+n);
	for(int i=1;i<=n;i++) 
		cout<<d[i]<<" ";	
	return 0;
}


