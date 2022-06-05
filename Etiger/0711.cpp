#include <bits/stdc++.h>
using namespace std;
struct Query {
	int l, r, id, blockID;
};
bool cmp(const Query&a, const Query&b) {
	if (a.blockID != b.blockID) return a.blockID < b.blockID;
	if (a.blockID & 1) return a.r < b.r;
	return a.r > b.r;
}
int n, m, x[100009], cnt[1000009], ans[100009];
Query q[100009];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> x[i];
	for (int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r;
	int L = n / sqrt(2 * m);
	for (int i = 1; i <= m; i++) {
		q[i].id = i;
		q[i].blockID = (q[i].l - 1) / L + 1;
	}
	sort(q + 1, q + m + 1, cmp);
	int l = 0, r = 0, cUnq = 0;
	for (int i = 1; i <= m; i++) {
		while (l > q[i].l) cUnq += (++cnt[x[--l]] == 1);
		while (l < q[i].l) cUnq -= (--cnt[x[l++]] == 0);
		while (r < q[i].r) cUnq += (++cnt[x[++r]] == 1);
		while (r > q[i].r) cUnq -= (--cnt[x[r--]] == 0);
		ans[q[i].id] = (cUnq == (r - l + 1));
	}
	for (int i = 1; i <= m; i++) {
		cout << (ans[i] ? "Yes" : "No") << endl;
	}
	return 0;
}
