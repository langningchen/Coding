#include<iostream>
using namespace std;
const int R=4;
const int N=10;
int cnt[R],x;
int main(){
	for(int i=0;i<N;i++) {
		cin>>x;
		cnt[x]++;
	}
	for(int i=1;i<=R-1;i++)
		for(int j=1;j<=cnt[i];j++)
			cout<<i<<" ";
	return 0;
}


