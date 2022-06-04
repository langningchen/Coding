#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct Query {
	int l, r, id, blockID;
};
bool cmp(const Query&a, const Query&b) {
	if (a.blockID != b.blockID) return a.blockID < b.blockID;
	if (a.blockID & 1) return a.r < b.r;
	return a.r > b.r;
}
int n, m, k, x[N], cnt[N], ans[N];
Query q[N];
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> x[i];
	for (int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r;
	int L = n / sqrt(2 * m);
	for (int i = 1; i <= m; i++) {
		q[i].id = i;
		q[i].blockID = (q[i].l - 1) / L + 1;
	}
	sort(q + 1, q + m + 1, cmp);
	int l = 0, r = 0;
	for (int i = 1; i <= m; i++) {
		while (l > q[i].l) ++cnt[x[--l]];
		while (l < q[i].l) --cnt[x[l++]];
		while (r < q[i].r) ++cnt[x[++r]];
		while (r > q[i].r) --cnt[x[r--]];
		ans[q[i].id] = max_element(cnt + 1, cnt + 1 + k) - cnt;
	}
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}
