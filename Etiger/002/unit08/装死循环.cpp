#include<iostream>
using namespace std; 
int main(){
	while(1){
		cout<<"Please input your password: ";
		int password;
		cin>>password;
		if(password==2333){
			cout<<"You have $1000000."<<endl;
			break;
		} else 
			cout<<"Wrong!"<<endl;
	}
	return 0;
}



