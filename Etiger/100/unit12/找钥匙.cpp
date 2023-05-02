#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	getline(cin,s);
	s=" "+s+" ";
	int p=s.find(" key ");
	cout<<p<<endl;
	return 0;	
} 


