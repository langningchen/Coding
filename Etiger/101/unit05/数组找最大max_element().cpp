#include<iostream>
#include<algorithm>
using namespace std;
int f[5]={3,1,5,1,2};
int main(){	
	cout<<max_element(f,f+5)<<endl;
	cout<<max_element(f,f+5)-f<<endl;
	cout<<*max_element(f,f+5)<<endl;	
	return 0;
}


