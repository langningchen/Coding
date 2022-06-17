#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
const int INF = 0x7FFFFFFF;
int n, m, a[N], c[N], ans = INF, ansl, ansr;
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int l = 0, r = 0, cnt = 0;
	while (r < n) {
		if (cnt < m) {
			c[a[r]]++;
			if (c[a[r]] == 1) cnt++;
			r++;
		}
		else {
			c[a[l]]--;
			if (c[a[l]] == 0) cnt--;
			l++;
		}
		if (cnt == m && r - l + 1 < ans) {
			ans = r - l + 1;
			ansl = l;
			ansr = r;
		}
	}
	cout << ansl + 1 << " " << ansr << endl;
	return 0;
}
