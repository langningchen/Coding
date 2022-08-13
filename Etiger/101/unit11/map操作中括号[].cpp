#include<iostream>
#include<map>
#include<string>
using namespace std;
int main(){
	map<char,string> d;
	d['a']="wawawa";
	d['b']="hahaha";
	d['c']=d['a'];
	d['b']="hohoho";
	cout<<d['a']<<endl;
	cout<<d['b']<<endl;
	cout<<d['c']<<endl;
	cout<<d['x']<<endl;
	cout<<"END"<<endl;
  	return 0;
}


