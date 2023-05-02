#include<iostream>
using namespace std;
const int N=10000;
int n,m,d[N],s[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>d[i];
	s[0]=0;
	for(int i=1;i<=n;i++) s[i]=s[i-1]+d[i];	
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		cout<<1000+s[x]<<" ";
	}	
	return 0;
}
	
