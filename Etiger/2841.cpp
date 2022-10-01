#include <bits/stdc++.h>
using namespace std;
int main()
{
	freopen("candy.in", "r", stdin);
	freopen("candy.out", "w", stdout);
	int n, l, r;
	cin >> n >> l >> r;
	cout << min((l / n) * n + n - 1, r) % n << endl;
	return 0;
}
