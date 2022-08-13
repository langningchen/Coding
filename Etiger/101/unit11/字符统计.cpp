#include<iostream>
#include<string>
#include<map>
using namespace std;
int main() {
	map<char,int> d;
	map<char,int>::iterator mit;
	string s;
	getline(cin,s);
	for(int i=0;i<s.size();i++)
		d[s[i]]++;
	for(mit=d.begin();mit!=d.end();mit++)
		cout<<mit->first<<" "<<mit->second<<endl;
	return 0;
}

