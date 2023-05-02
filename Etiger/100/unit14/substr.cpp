#include<iostream>
#include<string>
using namespace std;
int main() {
	string s="310101200802291472";
	cout<<s.substr(0,3)<<endl;
	cout<<s.substr(3,3)<<endl;
	cout<<s.substr(6,4)<<endl;
	cout<<s.substr(10,2)<<endl;
	cout<<s.substr(12,2)<<endl;
	return 0;	
} 


