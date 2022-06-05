#include <bits/stdc++.h>

using namespace std;

const int N = 100001;
vector<int> to[N];
int p[N], d[N], sz[N], h[N];

void dfs(int u, int fa) {
    p[u] = fa;
    d[u] = d[fa] + 1;
    sz[u] = 1;
    h[u] = 1;
    for (int i = 0; i < to[u].size(); i++) {
        if (to[u][i] == fa) {
            continue;
        }
        dfs(to[u][i], u);
        sz[u] += sz[to[u][i]];
        h[u] = max(h[u], h[to[u][i]] + 1);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << p[i] << " " << d[i] << " " << sz[i] << " " << h[i] << endl;
    }
    return 0;
}
