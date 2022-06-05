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
bool kruskal() {
    sort(e, e + m, cmp);
    for (ll i = 1; i <= n; i++) id[i] = i;
    ll ans = 0;
    for (ll k = 0; k < m; k++) {
        ll fa = find(e[k].a), fb = find(e[k].b);
        if (fa == fb) continue;
        id[fa] = fb;
        if (find(1) == find(n)) return 1;
    }
    return 0;
}
int main() {
//    freopen("lightkungfu2.in", "r", stdin);
//    freopen("lightkungfu2.out", "w", stdout);
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        node temp;
        cin >> temp.a >> temp.b;
        temp.w = 0;
        e[i] = temp;
    }
    int temp = 0;
    int j = 0;
    while (temp == 0) {
        for (int i = 0; i < m; i++)
            e[i].w += 1;
        temp = kruskal();
        j++;
    }
    cout << j << endl;
    return 0;
}
