#include<iostream>
#include<string>
using namespace std;
int main() {
	string s="pineapple";
	s.erase(0,4);
	cout<<s<<endl;
	s.erase(3);
	cout<<s<<endl;
	s.erase(0,1);
	cout<<s<<endl;
	return 0;	
} 


