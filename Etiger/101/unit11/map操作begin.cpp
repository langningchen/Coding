#include<iostream>
#include<map>
#include<string>
using namespace std;
int main(){
	map<string,int> cnt;
	cnt["Mike"]=1;
	cnt["John"]=2;
	cnt["Peter"]=3;
	map<string,int>::iterator mit;
	mit=cnt.begin();	
	cout<<(*mit).first<<" ";
	cout<<(*mit).second<<endl;
	cout<<mit->first<<" ";
	cout<<mit->second<<endl;
  	return 0;
}


