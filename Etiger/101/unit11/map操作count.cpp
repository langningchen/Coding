#include<iostream>
#include<map>
using namespace std;
int main(){
  	map<char,int> d;
  	d['a']=50; 	
	d['b']=100;
   	cout<<d.count('a')<<endl;
   	cout<<d.count('b')<<endl;
   	cout<<d.count('x')<<endl;
   	//cout<<d.size()<<endl;
	return 0;
}



