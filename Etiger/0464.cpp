#include <bits/stdc++.h>
using namespace std;
const char N = 6;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char ch, d[N][N];
int a, b, n = 5;
void dfs(int x, int y) {
    d[x][y] = 'G';
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && d[nx][ny] == ch)
            dfs(nx, ny);
    }
}
int main() {
    freopen("gold.in","r",stdin);
    freopen("gold.out","w",stdout);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> d[i][j];
    cin >> a >> b;
    ch = d[a][b];
    if (ch != 'G') dfs(a, b);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << d[i][j];
        cout << endl;
    }
    return 0;
}
