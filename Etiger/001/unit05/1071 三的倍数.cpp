#include<iostream>
using namespace std;   //使用标准名字空间 
int main(){
	int n;   //定义变量
	cin>>n;   //输入并赋值变量
	//if (n <= 1000)
	//{
	if (n % 3 == 0)   //判断 
		cout<<"Yes";   //输出
	else
		cout<<"No";   //输出
	//}
	//else
	//	printf("input wrong");
}
