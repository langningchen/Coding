#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	long long x=10;
	for(int i=2;i<=n;i++){
		x=x+x/2;
	}
	cout<<x<<endl;
	return 0;
} 


