#include<iostream>
#include<map>
using namespace std;
int main(){
  	map<char,int> d;
  	map<char,int>::iterator it;
  	// insert some values:
  	d['a']=10; d['b']=20;
  	d['c']=30; d['d']=40;
  	d['e']=50; d['f']=60;
  	it=d.find('b');
  	if(it!=d.end()) d.erase(it); // erasing by iterator
  	d.erase('c');  // erasing by key
  	d.erase('x');  // erasing by key
  	// show content:
  	for(it=d.begin(); it!=d.end(); ++it)
    	cout<<it->first<<" "<<it->second<<endl;
  	return 0;
}



