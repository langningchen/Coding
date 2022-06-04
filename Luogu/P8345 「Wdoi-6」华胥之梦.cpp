#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull INF = 0x7FFFFFFF;
const ull N = 10000005;
ull a[N];
int main() {
	ull n, c, q;
	cin >> n >> c >> q;
	for (ull i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ull i = 0; i < q; i++) {
		ull l;
		cin >> l;
		ull MAX = 0, MIN = INF, SUM = 0;
		for (ull j = 0; j < l; j++) {
			ull s;
			cin >> s;
			MAX = max(MAX, a[s - 1]);
			MIN = min(MIN, a[s - 1]);
			SUM += a[s - 1];
		}
		cout << (l - 1) * c - SUM + 2 * MIN - MAX << endl;
	}
	return 0;
}
