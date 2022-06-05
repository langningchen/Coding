#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
long long n, m, h[30000], x[30000];
int main() {
	cin >> n >> m;
	for (long long i = 1; i <= n; i++)
		cin >> x[i];
	h[1] = x[1];
	for (long long i = 2; i <= n; i++) {
		h[i] = 0;
		if (i > m - 1) h[i] = max(h[i], h[i - m + 1] + x[i]);
		if (i > m) h[i] = max(h[i], h[i - m] + x[i]);
		if (i > m + 1) h[i] = max(h[i], h[i - m - 1] + x[i]);
	}
	cout << *max_element(h + n - m + 1, h + n + 1) << endl;
	return 0;
}
