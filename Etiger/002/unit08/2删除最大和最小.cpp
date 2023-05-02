#include<iostream>
using namespace std;
const int N=109;
int n,f[N];
int main(){	
	cin>>n;
	for(int i=0;i<n;i++) cin>>f[i];
	int big=f[0];
	for(int i=1;i<n;i++){
		if(f[i]>big){
			big=f[i];
		}
	}
	int small=f[0];
	for(int i=1;i<n;i++){
		if(f[i]<small){
			small=f[i];
		}
	}
	for(int i=0;i<n;i++){
		if(f[i]!=big&&f[i]!=small){
			cout<<f[i]<<" ";
		}
	}
	return 0;
}



