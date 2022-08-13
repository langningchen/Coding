#include<iostream>
#include<ctime> 
using namespace std;
void SLEEP(int x){ //自己创造了一个函数，功能是延时x毫秒。100会学到如何自己创建函数 
	long long now=clock(); 
	while(clock()-now < x) ; //002y会学到这种神奇的写法 
} 
int main(){
	cout<<"开始倒计时"<<endl; 
	int i=10; 
	while(i){
		cout<<i<<endl;
		SLEEP(1000); //延时1秒
		i--;
	}
	cout<<"编程真有趣！"<<endl;	
	return 0;
}



