#include<bits/stdc++.h>
using namespace std;
const int N=200009;
string str;
bool b[N];
int n,sum[N];
int main(){
	cin>>str;
	n=str.size();
	for(int i=0;i<n;i++)
		if(str[i]=='B') b[i+1]=1;
		else b[i+1]=0;
	sum[0]=0;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
	for(int i=1;i<=n;i++)cout<<sum[i]<<" ";
	return 0;
}


