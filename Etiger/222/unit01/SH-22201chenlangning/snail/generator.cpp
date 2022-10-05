#include <bits/stdc++.h>
using namespace std;
const long long N = 100000000;
int main()
{
	srand(time(NULL));
	freopen("snail.in", "w", stdout);
	cout << (rand() % N) << " " << (rand() % N) << " " << (rand() % N) << endl;
	return 0;
}

