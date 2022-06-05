#include <bits/stdc++.h>
using namespace std;
int s[605];
int n, w;
int main() {
	freopen("live.in", "r", stdin);
	freopen("live.out", "w", stdout);
	cin >> n >> w;
	for (int p = 0; p < n; p++) {
		int Value = 0;
		cin >> Value;
		s[Value]++;
		int Index = max(1, (int)floor((p + 1) * w / 100.0));
		int Sum = 0;
		for (int i = 600; i >= 0; i--) {
			Sum += s[i];
			if (Sum > Index - 1) {
	            cout << i << " ";
				break;
			}
		}
	}
	return 0;
}
