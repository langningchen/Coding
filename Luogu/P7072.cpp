#include <bits/stdc++.h>
using namespace std;
const int N = 605;
int n, w, t[N];
int main()
{
	cin >> n >> w;
	for (int i = 1; i <= n; i++)
	{
		int tmp;
		cin >> tmp;
		t[tmp]++;
		int sum = 0;
		for (int j = 600; j >= 0; j--)
		{
			sum += t[j];
			if (sum >= max(1, i * w / 100))
			{
				cout << j << " ";
				break;
			}
		}
	}
	return 0;
}
