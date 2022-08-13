#include<iostream>
#include<algorithm>
using namespace std;
int f[5]={3,1,5,1,2};
int main(){	
	cout<<f<<endl;
	cout<<f+1<<endl;
	cout<<f+2<<endl;
	cout<<f+3<<endl;
	cout<<f+4<<endl;
	cout<<f+5<<endl;
	cout<<max_element(f,f+5)<<endl;	
	return 0;
}


