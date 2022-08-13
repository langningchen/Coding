#include<iostream>
using namespace std;
int a[2];
int main() {
	a[-1]=99;
	a[0]=100;
	a[1]=101;
	a[2]=102;
	a[3]=103;
	cout<<a[-1]<<endl;
	cout<<a[0]<<endl;
	cout<<a[1]<<endl;
	cout<<a[2]<<endl;
	cout<<a[3]<<endl;
	return 0;
}


