#include<iostream>
#include<map>
using namespace std;
int main(){
  	map<char,int> d;
  	map<char,int>::iterator it;
  	d['a']=50; 	
	d['b']=100;
  	d['c']=150; 
  	it=d.find('c');
    cout<<it->second<<endl;
	return 0;
}


