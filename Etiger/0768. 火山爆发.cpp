#include <bits/stdc++.h>
#define N 100
using namespace std;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int ans = 1, n, xS, yS, d[N][N];
bool vst[N][N];
struct Node{
    int x, y;
};
void bfs() {
    queue<Node> q;
    vst[xS][yS] = 1;
    q.push((Node){xS, yS});
    while (!q.empty()) {
        Node now = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = now.x + dx[k], ny = now.y + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && d[nx][ny] < d [now.x][now.y] && !vst[nx][ny]) {
                vst[nx][ny] = 1;
                q.push((Node){nx, ny});
                ans++;
            }
        }
    }
}
int main() {
    freopen("volcano.in","r",stdin);
    freopen("volcano.out","w",stdout);
    cin >> n >> xS >> yS;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> d[i][j];
    bfs();
    cout << n * n - ans << endl;
    return 0;
}
