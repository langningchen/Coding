#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct student{
	string name;
	int id,s;
};
student d[109];
bool cmp(const student&a,const student&b){
	if(a.s>b.s) return true;
	if(a.s<b.s) return false;
	if(a.id<b.id) return true;
	return false;
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>d[i].id>>d[i].name>>d[i].s;
	sort(d,d+n,cmp);	
	for(int i=0;i<n;i++){
		cout<<d[i].id<<" ";
		cout<<d[i].name<<" ";
		cout<<d[i].s<<endl;
	}
	return 0;
}


