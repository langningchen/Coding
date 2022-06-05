#include <bits/stdc++.h>
#define N 509
using namespace std;
int n, w, r, x[N], y[N];
bool vst[N], d[N][N];
double sqdlist(int i, int j) {
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}
void bfs() {
    queue<int> q;
    vst[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int k = n + 1; k >= 1; k--) {
            if (d[now][k] && !vst[k]) {
                vst[k] = 1;
                q.push(k);
            }
        }
    }
}
int main() {
    freopen("light.in","r",stdin);
    freopen("light.out","w",stdout);
    cin >> n >> w >> r;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) d[0][i] = y[i] <= r;
    for (int i = 1; i <= n; i++) d[i][n + 1] = y[i] + r >= w;
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++)
            if (sqdlist(i, j) <= 4 * r * r)
                d[i][j] = d[j][i] = 1;
    bfs();
    if (vst[n + 1])
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
