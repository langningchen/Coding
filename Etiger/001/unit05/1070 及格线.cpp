#include<iostream>
using namespace std;   //使用标准名字空间 
int main(){
	int score;   //定义变量 
	cin>>score;   //输入并赋值变量 
	//if (score >= 0 && score <= 100)
	//{
		if (score >= 60)   //判断 
			cout<<"Pass";   //输出 
		else   //判断
			cout<<"Fail";   //输出
	//}
	//else
	//	printf("input wrong");
}
