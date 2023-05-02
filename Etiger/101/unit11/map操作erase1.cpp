#include<iostream>
#include<map>
using namespace std;
int main(){
  	map<char,int> d;
  	map<char,int>::iterator it;
  	d['a']=50; 	
	d['b']=100;
  	d['c']=150; 
  	it=d.find('b');
  	if(it!=d.end())
    	d.erase(it);    
    for(it=d.begin();it!=d.end();++it)
    	cout<<it->second<<endl;
	return 0;
}


