#include<iostream>
using namespace std;
int main(){
	int p;
	cin>>p;
	int ans=1;
	for(int i=1;i<=p;i++){
		ans*=2;
	}
	cout<<ans<<endl;
	return 0;
} 


