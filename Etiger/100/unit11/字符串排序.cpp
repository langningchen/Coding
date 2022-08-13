#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int M=10;
string d[M]={"New York","Shanghai","Hong Kong",
			"London","Tokyo","Paris","Singapore",
			"Barcelona","Berlin","Beijing"};
int main(){
	for(int i=0;i<M;i++) cout<<d[i]<<endl;
	cout<<"*********\n";
	sort(d,d+M);
	for(int i=0;i<M;i++) cout<<d[i]<<endl;	
	return 0;
}


