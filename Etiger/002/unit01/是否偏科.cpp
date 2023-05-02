#include<iostream>
using namespace std;
int main() {
	int c,m;
	cin>>c>>m;
	if(c-m>30||m-c>30)
		cout<<"同学，你偏科啦！";
	else
		cout<<"哟！发展很均衡嘛！"; 
	return 0;
} 


