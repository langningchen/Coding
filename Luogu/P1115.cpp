#include <bits/stdc++.h>
using namespace std;
int n, ans, f;
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		f = max(f + a, a);
		ans = max(f, ans);
	}
	cout << ans << endl;
	return 0;
}
