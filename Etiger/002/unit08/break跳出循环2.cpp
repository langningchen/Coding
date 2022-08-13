#include<iostream>
using namespace std; 
int main(){
	int n=11;
	int i;
	for(i=2;i<=n-1;i++){
		if(n%i==0)
			break;
	}
	cout<<i<<endl;
	return 0;
}



