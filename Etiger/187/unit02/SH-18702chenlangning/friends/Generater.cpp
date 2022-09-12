#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int main()
{
	freopen("friends.in", "w", stdout);
	cout << N << " " << N << endl;
	for (int i = 0; i < N; i++)
		cout << rand() % 2000000 + 1000000 << " ";
	cout << endl;
	for (int i = 0; i < N; i++)
		cout << rand() % N << " " << rand() % N << endl;
	return 0;
}
