#include<bits/stdc++.h>
using namespace std;
const int N=1009;
int n,a,w[N];
int main(){
	cin>>n>>a;
	for(int i=0;i<n;i++)cin>>w[i];
	for(int i=0;i<n;i++)
		if(w[i]>a){
			cout<<-1<<endl;
			return 0;
		}
	int ans=1,sum=0;
	for(int i=0;i<n;i++){
		sum+=w[i];
		if(sum>a){
			ans++;
			sum=w[i];
		}
	}
	cout<<ans<<endl;	
	return 0;
}



