#include <bits/stdc++.h>
using namespace std;
struct Node{
	long long l, r;
};
bool cmp(const Node& cmp1, const Node& cmp2) {
	if (cmp1.l != cmp2.l) return cmp1.l < cmp2.l;
	else return cmp1.r < cmp2.r;
}
Node subway[100005];
long long L, M, l, r, s = -1, e = -2;
int main() {
	freopen("tree2.in", "r", stdin);
	freopen("tree2.out", "w", stdout);
	cin >> L >> M;
	L++;
	for (int i = 0; i < M; i++) {
		cin >> subway[i].l >> subway[i].r;
		if (subway[i].r < subway[i].l) swap(subway[i].r, subway[i].l);
	}
	sort(subway, subway + M, cmp);
	cout << endl << endl;
	for (int i = 0; i < M; i++) {
		if (subway[i].l < e) e = max(e, subway[i].r);
		else {
			L -= (e - s + 1);
			s = subway[i].l;
			e = subway[i].r;
		}
	}
	if (s != -1) L -= (e - s + 1);
	cout << L << endl;
	return 0;
}
