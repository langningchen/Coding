#include<iostream>
using namespace std;   //使用标准名字空间 
int main(){
	int n,a;   //定义变量
	cin>>n;   //输入并赋值变量
	//if (n <= 100000 && n >= 0)
	//{
	if (n >= 100)   //判断 
		a = n*7;   //计算 
	else   //判断
		a = n*10;   //计算
	cout<<a;   //输出
	//}
	//else
	//	printf("input wrong");
}
