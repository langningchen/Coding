#include<iostream>
#include<string>
using namespace std;
int main(){
	string s="water";
	s+="melon";
	cout<<s<<endl;
	cout<<s.length()<<endl;
	cout<<s.substr(0,5)<<endl;
	cout<<s.substr(5)<<endl;
	s.erase(0,5);
	cout<<s<<endl;
	s.insert(0,"hami ");
	cout<<s<<endl;
	return 0;	
} 


