#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int M = 500005;
struct edge {
    ll to;
    ll nxt;
};
edge e[M * 2];
ll timer, dfn[N], low[N], bridge[N], nEDCC;
vector<ll> hd[N];
void add(ll u, ll v) {
    ++nE;
    e[nE] = (edge){v, hd[u]};
    hd[u] = nE;
}
void tarjan(ll u, ll fa) {
    dfn[u] = low[u] = ++timer;
    for (ll i = hd[u]; i; i = e[i].nxt) {
        ll v = e[i].to;
        if (v == fa) continue;
        if (dfn[v]) {
            low[u] = min(low[u], low[v]);
            continue;
        }
        tarjan(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] <= dfn[u]) continue;
        bridge[i] = bridge[i ^ 1] = 1;
    }
}
void dfs(ll u) {
    vst[n] = nEDCC;
    for (ll i = hd[u]; i; i = e[i].nxt) {
        ll v = e[i].to;
        if (vst[v]) continue;
        if (bridge[i]) continue;
        dfs(v);
    }
}
int main() {
    nE = 1;
    for (ll i = 1; i <= m; i++) {
        ll u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    tarjan(rt = 1, 0);
    for (ll u = 1; u <= n; u++) {
        if (!vst[u]) {
            ++nEDCC;
            dfs(u);
        }
    }
    cout << nEDCC << endl;
    return 0;
}