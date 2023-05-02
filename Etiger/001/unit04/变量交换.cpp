#include<iostream> 
using namespace std;
int main() {
	int a,b,x;   
	cin>>a>>b;	
	cout<<a<<" "<<b<<endl;  
	x=a; //把a里面的值，放到x里面 
	a=b; //把现在b里面的值，放到a里面去 
	b=x; //把x里面的值（已经是最早a里面的值了） 又赋值给b 
	cout<<a<<" "<<b<<endl;  
	return 0;
}


