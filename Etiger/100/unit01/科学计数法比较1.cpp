#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	double x=0.00001234;
	cout<<x<<endl;
	cout<<fixed<<x<<endl;
	cout<<fixed<<setprecision(8)<<x<<endl;
	return 0;
}




