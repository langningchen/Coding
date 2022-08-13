#include<iostream>
#include<set> //引入set库 
using namespace std;
int main() {
	multiset<int> s;  //定义包含整数的set 
	multiset<int>::iterator it;	//定义迭代器 
	s.insert(6);	 
	if(s.find(6)!=s.end())cout<<"Found!"<<endl;
	else cout<<"Not found!"<<endl;
	if(s.find(7)!=s.end())cout<<"Found!"<<endl;
	else cout<<"Not found!"<<endl;
	return 0;
}




