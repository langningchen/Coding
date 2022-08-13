#include<iostream>
#include<set> 										//引入set库 
using namespace std;
int main() {
	set<int> s;  									//定义包含整数的set 
	s.insert(6);	 
	if(s.find(6)!=s.end())
		cout<<"Yes"<<endl;
	else 
		cout<<"No"<<endl;
	return 0;
}




