#include<iostream>
using namespace std;
int a[10];
int main() {
	for(int i=0;i<=9;i++)
		cin>>a[i];
	for(int i=9;i>=0;i--)
		cout<<a[i]<<endl;
	return 0;
} 
