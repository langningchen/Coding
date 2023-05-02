#include<iostream>
using namespace std;
int f[10];
int main(){
	for(int i=0;i<10;i++)
		cin>>f[i];
	int small=f[0];
	for(int i=1;i<10;i++)
		if(f[i]<small)
			small=f[i];
	for(int i=0;i<10;i++)
		if(f[i]!=small)
			cout<<f[i]<<" "; 
	return 0;
} 


