#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	getline(cin,s);
	int a=s.find(" ");
	int b=s.find(" ",a+1);
	s.erase(a+1,b-a-1);
	s.insert(a+1,"***");
	cout<<s<<endl;
	return 0;	
} 


