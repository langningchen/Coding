#include <bits/stdc++.h>
using namespace std;
const int M = 5005;
const int N = 105;
struct edge{int u, v, w;}; 
edge e[M];
int n, m, id[N];
int root(int u) {
    return id[u] == u ? u : id[u] = root(id[u]); 
}
bool cmp(const edge&a, const edge&b) {
    return a.w > b.w;
}
void Kruskal() {
    sort(e, e + m, cmp);
    for (int u = 1; u <= n; u++) id[u] = u;
    int ans = 0;
    for (int k = 0; k < m; k++) {
        int ru = root(e[k].u);
        int rv = root(e[k].v);
        if (ru == rv) continue;
        id[ru] = rv;
        ans += e[k].w;
    }
    cout << ans << endl;
}
int main() {
//    freopen("bridge.in","r",stdin);
//    freopen("bridge.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;
    Kruskal();
    return 0;
}
