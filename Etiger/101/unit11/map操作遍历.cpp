#include<iostream>
#include<map>
using namespace std;
int main(){
  	map<char,int> d;
	d['b'] = 100;
  	d['a'] = 200;
  	d['c'] = 300;
  	map<char,int>::iterator it;
  	for(it=d.begin();it!=d.end();++it)
    	cout<<it->first<<" "<<it->second<<endl;
  	for(it=d.begin();it!=d.end();++it)
    	cout<<(*it).first<<" "<<(*it).second<<endl;
	return 0;
}

