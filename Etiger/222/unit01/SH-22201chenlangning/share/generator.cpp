#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
int main()
{
	srand(time(NULL));
	freopen("share.in", "w", stdout);
	cout << N << " " << (rand() % 1000000) << endl;
	for (int i = 0; i < N; i++)
	    cout << (rand() % 20000 - 10000) << " ";
	return 0;
}
