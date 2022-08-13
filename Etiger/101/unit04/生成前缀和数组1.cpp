#include<iostream>
using namespace std;
int s[6],x[6];
int main(){
	for(int i=1;i<=5;i++) cin>>x[i];
	s[0]=0;
	for(int i=1;i<=5;i++) s[i]=s[i-1]+x[i];
	for(int i=1;i<=5;i++) cout<<s[i]<<' ';	
	return 0;
}
	
	
