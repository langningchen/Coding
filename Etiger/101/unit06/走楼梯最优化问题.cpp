/*
h[i]记录:共i级时最高能走到第几级
输入样例n=10,a=3,b=4
   i=0,1,2,3,4,5,6,7,8,9,10
h[i]=0,0,0,3,4,4,6,7,8,9,10
*/
#include<iostream>
#include<algorithm>
using namespace std;
int n,a,b,h[100];
int main(){
	cin>>n>>a>>b;
	h[0]=0; 
	for(int i=1;i<=n;i++){
		h[i]=h[i-1];
		if(i>=a) h[i]=max(h[i],h[i-a]+a);
		if(i>=b) h[i]=max(h[i],h[i-b]+b);
	}
	for(int i=0;i<=n;i++)
		cout<<i<<":"<<h[i]<<endl;
	return 0;
}


