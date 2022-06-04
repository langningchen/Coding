#include <bits/stdc++.h>
using namespace std;
const int N = 200009;
int n, m, s[N], x[N];
int main() {
	freopen("dog.in", "r", stdin);
	freopen("dog.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	for (int i = n + 1; i <= n * 2; i++)
		x[i] = x[i - n];
	s[0] = 0;
	for (int i = 1; i <= n * 2; i++)
		s[i] = s[i - 1] + x[i];
	int ans = s[m];
	for (int i = m + 1; i <= n * 2; i++)
		ans = max(ans, s[i] - s[i - m]);
	cout << ans;
	return 0;
}
