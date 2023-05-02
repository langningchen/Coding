#include<iostream>
#include<set>
using namespace std;
int main() {
	multiset<int> s;
	s.insert(9); s.insert(8);
	s.insert(7); s.insert(6); 
	multiset<int>::reverse_iterator it;
	it=s.rbegin();  it++;
	cout<<*it<<endl;
	return 0;
}

