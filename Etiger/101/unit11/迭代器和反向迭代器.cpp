#include<iostream>
#include<set>
using namespace std;
int main() {
	multiset<int> s;
	s.insert(9); s.insert(8); s.insert(7);
	s.insert(1); s.insert(2); s.insert(3);
	multiset<int>::iterator it;
	for(it=s.begin();it!=s.end();it++)
		cout<<*it;
	cout<<endl<<"------"<<endl;
	multiset<int>::reverse_iterator rit;
	for(rit=s.rbegin();rit!=s.rend();rit++)
		cout<<*rit;
	return 0;
}


