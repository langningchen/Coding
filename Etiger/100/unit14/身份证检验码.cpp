#include<iostream>
#include<string>
using namespace std;
int a[20]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
char code[20]={'1','0','X','9','8','7','6','5','4','3','2'};
int main(){
	string s;
	cin>>s;
	int sum=0;
	for(int i=0;i<=16;i++)
		sum+=(s[i]-'0')*a[i];
	sum%=11;
	cout<<code[sum]<<endl;
	return 0;	
} 


