#include<iostream>
#include<algorithm>
using namespace std;
const int N=1009;
struct drink{
	int q,p;
};
drink d[N];
bool cmp(const drink&a,const drink&b){
	return ________;
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>d[i].q>>d[i].p;
	sort(d,d+n,cmp);
	int ans=0,c=____;
	for(int i=0;______;i++){
		int x=min(______);
		ans+=_______;
		c-=x;
	}
	cout<<____<<endl;	
	return 0;
}

