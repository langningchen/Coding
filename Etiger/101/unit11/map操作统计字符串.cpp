#include<iostream>
#include<map>
#include<string>
using namespace std;
int main(){
	map<string,int> cnt;
	cnt["Mike"]++;
	cnt["John"]++;
	cnt["Mike"]++;
	cnt["Peter"]++;
	cout<<cnt["Mike"]<<endl;
	cout<<cnt["John"]<<endl;
	cout<<cnt["Peter"]<<endl;
  	return 0;
}


