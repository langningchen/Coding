#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
int n, m, l, r, x[N], st1[20][N], st2[20][N];
void ST() {
    for (int i = 1; i <= n; i++)
        st1[0][i] = st2[0][i] = x[i];
    int p = log(n) / log(2);
    for (int k = 1; k <= p; k++)
        for (int i = 1; i <= n - (1 << k) + 1; i++) {
            st1[k][i] = max(st1[k - 1][i], st1[k - 1][i + (1 << (k - 1))]);
            st2[k][i] = min(st2[k - 1][i], st2[k - 1][i + (1 << (k - 1))]);
        }
}
int query(int l, int r) {
    int p = log(r - l + 1) / log(2);
    return max(st1[p][l], st1[p][r - (1 << p) + 1]) - min(st2[p][l], st2[p][r - (1 << p) + 1]);
}
int main() {
    freopen("stock2.in", "r", stdin);
    freopen("stock2.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    ST();
    for (int i = 1; i <= m; i++) {
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
    return 0;
}
