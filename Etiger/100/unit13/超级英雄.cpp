#include<iostream>
#include<string>
using namespace std;
struct hero{
	string name;
	int power;
};
hero h[10];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++) 
		cin>>h[i].name>>h[i].power;
	for(int i=0;i<n;i++) 
		cout<<h[i].name<<": "<<h[i].power<<endl;
	return 0;
}


