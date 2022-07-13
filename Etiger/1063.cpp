#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, q, p[N], x[N], y[N], ans[N], J[N], K[N], id[N];
bool cmp(const int &a, const int &b)
{
    return J[a] < J[b] || J[a] == J[b] && K[a] < K[b];
}
void solve()
{
    for (int i = 1; i <= q; i++)
        id[i] = i;
    sort(id + 1, id + 1 + q, cmp);
    for (int i = 1; i <= n; i++)
        y[i] = x[i] = i;
    for (int k = 1, j = 1; k <= q; k++)
    {
        for (; j <= J[id[k]]; j++)
        {
            swap(x[p[j]], x[p[j] + 1]);
            swap(y[x[p[j]]], y[x[p[j] + 1]]);
        }
        ans[id[k]] = y[K[id[k]]];
    }
    for (int i = 1; i <= q; i++)
        cout << ans[i] << endl;
}
int main()
{
    freopen("hat.in", "r", stdin);
    freopen("hat.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> p[i];
    cin >> q;
    for (int i = 1; i <= q; i++)
        cin >> K[i] >> J[i];
    solve();
    return 0;
}
