#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, B, a[N], b[N], ans[N];
vector<int> v[N];
int submit(int f) {
	int cnt = 0, j;
	for (j = 1; j <= b[n]; j++) {
		cnt += v[j].size();
		if (cnt >= f)
			break;
	}
	cnt -= v[j].size();
	int res = v[j][f - cnt - 1];
	v[j].erase(v[j].begin() + f - cnt - 1);
	return res;
}
int main() {
	freopen("submission.in", "r", stdin);
	freopen("submission.out", "w", stdout);
	cin >> n;
	B = sqrt(n);
	for (int i = 1; i <= n; i++) b[i] = (i - 1) / B + 1; 
	for (int i = 1; i <= n; i++) v[b[i]].push_back(i);
	for (int i = 1, f; i <= n; i++) {
		cin >> f;
		ans[i] = submit(f);
	}
	cout << ans[n - 1] << " " << ans[n] << endl;
	return 0;
}

