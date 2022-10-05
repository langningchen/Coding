#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
int main()
{
	srand(time(NULL));
	freopen("word.in", "w", stdout);
	cout << N << " " << N << endl;
	for (int i = 0; i < N; i++)
	{
	    for (int j = 0; j < N; j++)
	        cout << (char)(rand() % 26 + 'a');
	    cout << endl;
	}
	return 0;
}
