#include<iostream>
using namespace std;
int main(){
	int score;
	cin>>score;
	if(score>=80)
		cout<<"A"<<endl;
	else if(score>=60&&score<80)
		cout<<"B"<<endl;
	else if(score<60)
		cout<<"C"<<endl;
	return 0;
} 



