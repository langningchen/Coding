#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main(){
	double a,b,c,d;
	cin>>a>>b>>c>>d;
	double manhattan=fabs(c-a)+fabs(d-b);
	cout<<fixed<<setprecision(1)<<manhattan<<endl;
	return 0;
}
