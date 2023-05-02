#include<iostream>
#include<set> 							//引入set库 
using namespace std;
int main() {
	set<int> s;  						//定义包含整数的set 
	s.insert(7);						//插入元素 
	s.insert(5);
	s.insert(6);
	s.insert(5);	
	set<int>::iterator it;				//定义迭代器 
	for(it=s.begin();it!=s.end();++it)
		cout<<*it<<endl;
	return 0;
}




