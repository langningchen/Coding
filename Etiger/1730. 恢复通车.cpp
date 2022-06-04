#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, id[N];
int root(int x) { return ((id[x] == x)  ?  (x)  :  (id[x] = root(id[x]))); }
void unite(int x, int y) { id[root(x)] = root(y); }
int main() {
    freopen("transportation.in","r",stdin);
    freopen("transportation.out","w",stdout);
    cin >> m >> n;
    for (int i = 0; i < N; i++) {
        id[i] = i;
    }
    int cnt = m;
    for (int t = 1; t <= n; t++) {
        int u, v;
        cin >> u >> v;
        int ru = root(u);
        int rv = root(v);
         if (ru == rv) {
            continue;
        }
        unite(ru, rv);
        cnt--;
        if (cnt == 1) {
            cout << t << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
