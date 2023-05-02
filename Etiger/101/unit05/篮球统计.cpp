#include<iostream>
#include<iomanip>
using namespace std;
const int R=4;
int cnt[R],x;
int main(){
	while(cin>>x) cnt[x]++;
	double sum=cnt[3]*3+cnt[2]*2+cnt[1];
	cout<<fixed<<setprecision(1)<<cnt[3]*3/sum*100<<"%"<<endl;
	cout<<fixed<<setprecision(1)<<cnt[2]*2/sum*100<<"%"<<endl;
	cout<<fixed<<setprecision(1)<<cnt[1]/sum*100<<"%"<<endl;
	return 0;
}

