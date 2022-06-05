#include <bits/stdc++.h>
#define N 1009
using namespace std;
int m, n, a, b;
bool d[N][N], vst[N];
void bfs(int x) {
    queue<int> q;
    vst[x] = 1;
    q.push(x);
    while (!q.empty()) {
        int now = q.front();  q.pop();
        for (int k = 1; k <= n - 1; k++)
            if (!vst[k] && d[now][k]) {
                vst[k] = 1;
                q.push(k);
            }
    }
}
int main() {
    freopen("relation.in","r",stdin);
    freopen("relation.out","w",stdout);
    cin >> m >> n;
    for (int i = 1; i <=m; i++) {
        cin >> a >> b;
        d[a][b] = d[b][a] = 1;
    }
    bfs(0);
    if (vst[1]) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
