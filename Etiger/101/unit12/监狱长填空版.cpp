#include<bits/stdc++.h>
using namespace std;
const int N=1009;
int k,m,d[N];
int main(){
	cin>>k>>m;
	for(int i=0;i<k;i++)cin>>d[i];
	int p=0,cnt=1;
	for(int i=1;i<k;i++)
		if(d[i]-d[p]>=___){
			cnt++;
			p=___;			
		}
	cout<<____<<endl;	
	return 0;
}



