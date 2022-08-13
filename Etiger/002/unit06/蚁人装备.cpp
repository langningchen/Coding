#include<iostream>
#include<iomanip>
using namespace std;
double x,a[10];
int main(){
	for(int i=0;i<10;i++)
		cin>>a[i];
	cin>>x;
	for(int i=0;i<10;i++)
		cout<<fixed<<setprecision(1)<<a[i]/x<<" ";
	return 0;
}


