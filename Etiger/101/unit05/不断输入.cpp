#include<iostream>
using namespace std;
const int R=10;
int cnt[R],x;
int main(){
	while(cin>>x) 
		cnt[x]++;
	for(int i=0;i<R;i++)
		cout<<i<<":"<<cnt[i]<<endl;
	return 0;
}

