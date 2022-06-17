#include <bits/stdc++.h>
using namespace std;
int n, w, a[605];
int main() {
	cin >> n >> w;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x]++;
		int sum = 0;
		for (int j = 600; j >= 0; j--) {
			sum += a[j];
			if (j > max(1, i * w / 100)) {
				cout << j << " ";
				break;
			}
		}
	}
	return 0;
}
