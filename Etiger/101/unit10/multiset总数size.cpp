#include<iostream>
#include<set> 					//引入set库 
using namespace std;
int main() {
	multiset<int> ms;  			//定义包含整数的multiset 
	ms.insert(6); 
	ms.insert(6); 	
	ms.insert(7); 	
	cout<<ms.size()<<endl;	
	return 0;
}



