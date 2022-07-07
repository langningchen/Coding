#include <bits/stdc++.h>
using namespace std;
const int N = 1009;
int n, m, x, y, id[N];
int root(int x) { return ((id[x] == x)  ?  (x)  :  (id[x] = root(id[x]))); }
void unite(int x, int y) { id[root(x)] = root(y); }
int main() {
    freopen("relation.in","r",stdin);
    freopen("relation.out","w",stdout);
    cin >> m >> n;
    for (int i = 0; i < n; i++) id[i] = i;
    for (int i = 0; i < m; i++) { cin >> x >> y; unite(x, y); }
    if (root(1) == root(0)) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
