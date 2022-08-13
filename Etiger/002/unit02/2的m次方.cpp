#include<iostream>
using namespace std;
int main(){
	int m;
	cin>>m;
	int ans=1,i=1;
	while(i<=m){
		ans*=2;
		i++;
	}
	cout<<ans<<endl;
	return 0;
} 


