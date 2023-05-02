#include<iostream>
using namespace std;
void cry(int n){
	for(int i=0;i<n;i++)
		cout<<"5"; 
}
void orz(int n){	
	for(int i=0;i<n;i++)
		cout<<" O|--|_ "; 
}
int main(){
	cry(100);
	orz(200);
	cry(100);
	return 0;
}



