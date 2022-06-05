#include <bits/stdc++.h>
using namespace std;
const int N = 509;
struct Node{int x, y;};
int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
bool vst[N][N];
int r1, c1, r2, c2, d[N][N];
int n = 10, m = 9;
void bfs() {
    queue<Node> q;
    vst[r1][c1] = 1;
    d[r1][c1] = 0;
    q.push((Node){r1, c1});
    while (!q.empty()) {
        Node now = q.front(); q.pop();
        for (int k = 0; k < 8; k++) {
            int nx = now.x + dx[k], ny = now.y + dy[k];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vst[nx][ny]) continue;
            vst[nx][ny] = 1;
            d[nx][ny] = d[now.x][now.y] + 1;
            q.push((Node){nx, ny});
        }
    }
    if (!vst[r2][c2]) cout << -1 << endl;
    else cout << d[r2][c2] << endl;
}
int main() {
    freopen("horse.in","r",stdin);
    freopen("horse.out","w",stdout);
    cin >> r1 >> c1 >> r2 >> c2;
    bfs(); 
    return 0;
}
