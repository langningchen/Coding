#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, -1, 1, 0};
vector<vector<int>> to;
int cnt, R, C, id[N][N];
char d[N][N];
vector<int> level, vst;
void bfs()
{
    queue<int> q;
    level.resize(cnt + 1);
    vst.resize(cnt + 1);
    q.push(1);
    vst[1] = 1;
    level[1] = 1;
    int ans = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < to[u].size(); i++)
        {
            int v = to[u][i];
            if (vst[v])
                continue;
            vst[v] = 1;
            ans = level[v] = level[u] + 1;
            q.push(v);
        }
    }
    cout << ans << endl;
}
void dfs(int x, int y)
{
    id[x][y] = cnt;
    for (int k = 0; k < 4; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx < 1 || nx > R || ny < 1 || ny > C)
            continue;
        if (d[nx][ny] == d[x][y] && !id[nx][ny])
            dfs(nx, ny);
    }
}
void build()
{
    to.resize(cnt + 1);
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++)
        {
            if (d[x][y] == '*')
                continue;
            for (int k = 0; k < 4; k++)
            {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 1 || nx > R || ny < 1 || ny > C)
                    continue;
                if (d[nx][ny] == '*')
                    continue;
                if (d[nx][ny] == d[x][y])
                    continue;
                to[id[x][y]].push_back(id[nx][ny]);
            }
        }
}
int main()
{
    freopen("footprint.in", "r", stdin);
    freopen("footprint.out", "w", stdout);
    cin >> R >> C;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            cin >> d[i][j];
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            if (d[i][j] != '*' && !id[i][j])
            {
                cnt++;
                dfs(i, j);
            }
    build();
    bfs();
    return 0;
}
