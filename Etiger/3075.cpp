#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, nX, nY, x[N], y[N];
struct Info
{
    int v, id;
    bool operator<(const Info &x) const
    {
        return v > x.v || v == x.v && id > x.id;
    }
};
Info d[N];
int main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> n >> nX >> nY;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    for (int i = 1; i <= n; i++)
        cin >> y[i];
    for (int i = 1; i <= n; i++)
        d[i] = (Info){x[i] - y[i], i};
    sort(d + 1, d + 1 + n);
    int ans = 0;
    for (int i = 1; i <= nX; i++)
        ans += x[d[i].id];
    for (int i = nX + 1; i <= n; i++)
        ans += y[d[i].id];
    cout << ans << endl;
    return 0;
}