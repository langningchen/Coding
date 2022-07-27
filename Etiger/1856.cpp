#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int x, y
};
const int N = 2005;
Node rep[N * N];
int nID, n, m, q, rep[N], s[N][N], ok[N][N], id[N][N];
bool out(Node &o, int &r1, int &c1, int &r2, int &c2)
{
    return o.x < r1 || o.x > r2 || o.y < c1 || o.y > c2;
}
void dfs(int x, int y)
{
    id[x][y] = nID;
    for (int k = 0; k < 4; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx < 1 || nx > n || ny < 1 || ny > m)
            continue;
        if (d[nx][ny] == d[x][y] && !id[nx][ny])
            dfs(nx, ny);
    }
}
int main()
{
    // freopen("king.in", "r", stdin);
    // freopen("king.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!id[i][j])
            {
                ++nID;
                rep[nID] = (Node){i, j};
                ok[i][j] = 1;
                dfs(i, j);
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + ok[i][j];
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int nRepIn = s[r2][c2] + s[r1 - 1][c1 - 1] - s[r1 - 1][c2] - s[r2][c1 - 1];
        set<int> RepOut;
        int y = c1;
        for (int x = r1; x <= r2; x++)
            if (out(rep[id[x][y]], r1, c1, r2, c2))
                RepOut.insert(id[x][y]);
        y = c2;
        for (int x = r1; x <= r2; x++)
            if (out(rep[id[x][y]], r1, c1, r2, c2))
                RepOut.insert(id[x][y]);
        int x = r1;
        for (int y = c1; y <= c2; y++)
            if (out(rep[id[x][y]], r1, c1, r2, c2))
                RepOut.insert(id[x][y]);
        x = r2;
        for (int y = c1; y <= c2; y++)
            if (out(rep[id[x][y]], r1, c1, r2, c2))
                RepOut.insert(id[x][y]);
        int ans = nRepIn + RepOut.size();
        cout << ans << endl;
    }
    return 0;
}