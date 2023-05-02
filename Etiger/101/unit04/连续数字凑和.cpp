#include<iostream>
#define N 5009
using namespace std;
int n,m,s[N],d[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>d[i];
	s[0]=0;
	for(int i=1;i<=n;i++) s[i]=s[i-1]+d[i];
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(s[j]-s[i-1]==m){
				cout<<"Yes"<<endl;
				return 0;
			}
	cout<<"No"<<endl;	
	return 0;
}
	
	
