#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
const int INF = 1e9;
typedef long long ll;
ll n, m, id[N];
struct node {
    ll a, b, w;
} e[N];
int find(int x)
{
    return id[x] == x ? x : x = find(id[x]);
}
void bing(int x,int y)
{
    id[find(y)] = find(x);
}
bool cmp(const node &a, const node &b) {
    return a.w < b.w;
}
ll kruskal() {
    sort(e, e + m, cmp);
    for (ll i = 1; i <= n; i++) id[i] = i;
    ll ans = 0;
    for (ll k = 0; k < m; k++) {
        ll fa = find(e[k].a), fb = find(e[k].b);
        if (fa == fb) continue;
        id[fa] = fb;
        if (find(1) == find(n)) return e[k].w;
    }
    return -1;
}
int main() {
    freopen("romeo2.in", "r", stdin);
    freopen("romeo2.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        node temp;
        cin >> temp.a >> temp.b >> temp.w;
        e[i] = temp;
        bing(temp.a, temp.b);
    }
    cout << kruskal() << endl;
    return 0;
}
