#include <bits/stdc++.h>
using namespace std;
const int N = 20005;
typedef long long ll;
const ll INF = 1e9;
ll n, m, in[N], cnt[N], dst[N], x[N];
vector<ll> to[N], w[N];
bool spfa() {
    fill(dst, dst + n + 9, INF);
    queue<int> q;
    dst[1] = 0; in[1] = 1; cnt[1] = 1; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop(); in[u] = 0;
        for (int i = 0, v; i < to[u].size(); i++)
            if (dst[v = to[u][i]] > dst[u] + w[u][i]) {
                dst[v] = dst[u] + w[u][i];
                if (!in[v]) q.push(v), in[v] = 1, cnt[v]++;
                if (cnt[v] == n) return -1;
            }
    }
    return 0;
}
int main() {
    freopen("wulin4.in", "r", stdin);
    freopen("wulin4.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        to[b].push_back(a);
        w[b].push_back(c);
    }
    if (spfa() == -1) {
        cout << -1 << endl;
    }
    else {
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dst[i] != INF)
                ans += dst[i] * x[i];
        }
        if (ans < 0) {
            cout << -1 << endl;
        }
        else {
            cout << ans << endl;
        }
    }
    return 0;
}
