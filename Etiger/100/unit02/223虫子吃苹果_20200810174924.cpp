#include<bits/stdc++.h>
using namespace std;
int n;	
int x;	
int y;	
int m;	
int ans;
int main(){
	cin>>n>>x>>y;
	int m=ceil(y*1.0/x);
	int ans=max(n-m,0);
	cout<<ans<<endl;
	return 0;
}




