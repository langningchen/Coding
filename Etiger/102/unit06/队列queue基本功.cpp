#include<iostream>
#include<queue>
using namespace std;
int main(){
	queue<int> q;
	q.push(3);
	q.push(1);
	q.push(4);
	cout<<q.size()<<endl;
	cout<<q.front()<<endl;
	q.pop();
	cout<<q.size()<<endl;
	cout<<q.front()<<endl;
	q.pop();
	cout<<q.size()<<endl;
	cout<<q.front()<<endl;
	q.pop();
	cout<<q.size()<<endl;
	return 0;
}




