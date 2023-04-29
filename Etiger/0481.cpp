#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N], n;
bool OK(int x)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i] + a[j] == x)
				return 1;
	return 0;
}
int main()
{
	freopen("quiz.in", "r", stdin);
	freopen("quiz.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int cnt = 0;
	for (int k = 0; k < n; k++)
		if (OK(a[k]))
			cnt++;
	cout << cnt << endl;
	return 0;
}
