#include<iostream>
#include<string>
using namespace std;
int main(){
	string s="I am lucky";
	s.insert(5,"very "); 
	cout<<s<<endl;
	s.insert(10,"un"); 
	cout<<s<<endl;
	s.insert(5,"not "); 
	cout<<s<<endl;
	return 0;	
} 


