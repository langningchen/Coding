#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	getline(cin,s);
	int p;
	for(p=0;p<s.size();p++)
		if(s[p]==' ') break;
	s.erase(0,p);
	s.insert(0,"***");
	cout<<s<<endl;
	return 0;	
} 


