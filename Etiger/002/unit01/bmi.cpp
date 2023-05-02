#include<iostream>
using namespace std;
int main() {
	double w,h,bmi;
	cin>>w>>h;
	bmi=w/(h*h);
	if (bmi<=18.5)
		cout<<"hi,此人过轻";
	else if (bmi>18.5 && bmi<=24) 
		cout<<"hi,此人正常";
	else if (bmi>24 && bmi<=28) 
		cout<<"hi,此人过重";
	else if (bmi>28 && bmi<=32) 
		cout<<"hi,此人肥胖";
	else 
		cout<<"hi,此人非常肥胖";
	return 0;
} 


