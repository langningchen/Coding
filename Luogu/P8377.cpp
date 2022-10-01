#include <bits/stdc++.h>
using namespace std;
const int N = 1000001;
int ans[N + 5];
int a[N + 5];
int main()
{
	a[1] = a[2] = 1;
	ans[1] = 1;
	ans[2] = 2;
	for (int i = 3; i <= N; i++)
	{
		a[i] = (a[i - 1] + a[i - 2]) % 9;
		ans[i] = (ans[i - 1] + a[i]) % 9;
		cout << ans[i] << " ";
	}
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		cout << ans[n] << endl;
	}
	return 0;
}
