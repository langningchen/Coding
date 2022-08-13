#include<iostream>
#include<algorithm>
using namespace std;
int f[10]={3,5,12,1,6,7,9,8,3,1};
int main(){
	cout<<min_element(f,f+10)<<endl;
	cout<<min_element(f,f+10)-f<<endl;
	cout<<*min_element(f,f+10)<<endl;	
	cout<<max_element(f,f+10)<<endl;
	cout<<max_element(f,f+10)-f<<endl;
	cout<<*max_element(f,f+10)<<endl;	
	return 0;
}


