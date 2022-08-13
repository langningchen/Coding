#include<iostream>
#include<string>
using namespace std;
int main(){
	string s="wa ha ha";
	int p=s.find(" ",0); 
	cout<<p<<endl;
	p=s.find(" ",3); 
	cout<<p<<endl;
	p=s.find("ha",3); 
	cout<<p<<endl;
	p=s.find("ha",4); 
	cout<<p<<endl;
	p=s.find("ha",7); 
	cout<<p<<endl;
	return 0;
} 
