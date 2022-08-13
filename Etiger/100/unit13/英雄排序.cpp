#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct hero{
	string name;
	int power;
};
hero h[10];
bool cmp(const hero&a,const hero&b){
	if(a.power>b.power) return true;
	if(a.power<b.power) return false;
	if(a.name<b.name) return true;
	return false;
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++) 
		cin>>h[i].name>>h[i].power;
	sort(h,h+n,cmp);
	for(int i=0;i<n;i++) 
		cout<<h[i].name<<": "<<h[i].power<<endl;
	return 0;
}


