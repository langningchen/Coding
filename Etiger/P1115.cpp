#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7FFFFFFF;
int main() {
	int n, f, s = -INF;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		f = max(f + a, a);
		s = max(s, f);
	}
	cout << s << endl;
	return 0;
}
