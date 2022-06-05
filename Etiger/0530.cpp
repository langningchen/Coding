#include <bits/stdc++.h>
#define N 11
using namespace std;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int xR, yR, xJ, yJ, m, n, dst[N][N];
char d[N][N];
bool vst[N][N];
struct Node{
    int x, y;
};
int bfs() {
    queue<Node> q;
    vst[xR][yR] = 1;
    dst[xR][yR] = 0;
    q.push((Node){xR, yR});
    while (!q.empty()) {
        Node now = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = now.x + dx[k], ny = now.y + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && d[nx][ny] != '#' && !vst[nx][ny]) {
                vst[nx][ny] = 1;
                dst[nx][ny] = dst[now.x][now.y] + 1;
                q.push((Node){nx, ny});
                if (nx == xJ && ny == yJ) return dst[nx][ny];
            }
        }
    }
    return -1;
}
int main() {
    freopen("romeo.in","r",stdin);
    freopen("romeo.out","w",stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> d[i][j];
            if (d[i][j] == 'R') xR = i, yR = j;
            else if (d[i][j] == 'J') xJ = i, yJ = j;
        }
    int len = bfs();
    if (len == -1) cout << "forever" << endl;
    else cout << fixed << setprecision(1) << len / 2.0 << endl;
    return 0;
}
