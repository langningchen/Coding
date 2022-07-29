#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int a[N], n, ans;
int main()
{
	for (int i = 0; i < N; i++)
		cin >> a[i];
	cin >> n;
	for (int i = 0; i < N; i++)
		if (a[i] <= n + 30)
			ans++;
	cout << ans << endl;
	return 0;
}