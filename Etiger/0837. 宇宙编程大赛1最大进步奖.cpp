#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, l, r, x[N], y[N], st[20][N];
void ST() {
    for (int i = 1; i <= n; i++)
        st[0][i] = y[i];
    int p = log(n) / log(2);
    for (int k = 1; k <= p; k++)
        for (int i = 1; i <= n - (1 << k) + 1; i++)
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
}
int query(int l, int r) {
    int p = log(r - l + 1) / log(2);
    return min(st[p][l], st[p][r - (1 << p) + 1]);
}
int main() {
    freopen("improvement.in", "r", stdin);
    freopen("improvement.out", "w", stdout);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        y[x[i]] = i;
    }
    ST();
    for (int i = 1; i <= m; i++) {
        cin >> l >> r;
        cout << query(l, r) << " ";
    }
    return 0;
}
