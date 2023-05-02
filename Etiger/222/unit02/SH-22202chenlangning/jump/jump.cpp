#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 105;
const ll INF = 0x7FFFFFFF;
ll n, m, ma[N][N], cnt, ans = INF;
// stack<pair<pair<ll, ll>, pair<ll, ll>>> s;
bool vst[N][N];
const ll dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const ll dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
void dfs(int x, int y, int last_direction)
{
    if (cnt > ans)
        return;
    if (x == m && y == n)
    {
        // if (cnt < ans)
        // {
        //     cout << cnt << endl;
        //     stack<pair<pair<ll, ll>, pair<ll, ll>>> tmp;
        //     while (!s.empty())
        //     {
        //         tmp.push(s.top());
        //         s.pop();
        //     }
        //     while (!tmp.empty())
        //     {
        //         cout << tmp.top().first.first << " " << tmp.top().first.second << " " << tmp.top().second.first << " " << tmp.top().second.second << endl;
        //         s.push(tmp.top());
        //         tmp.pop();
        //     }
        //     cout << endl;
        // }
        ans = min(ans, cnt);
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i] * ma[x][y];
        int ny = y + dy[i] * ma[x][y];
        if (i == last_direction || nx < 1 || nx > m || ny < 1 || ny > n || vst[nx][ny])
            continue;
        cnt++;
        vst[nx][ny] = true;
        // s.push(make_pair(make_pair(x, y), make_pair(i, ma[x][y])));
        dfs(x + dx[i] * ma[x][y], y + dy[i] * ma[x][y], i);
        // s.pop();
        vst[nx][ny] = false;
        cnt--;
    }
}
int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> ma[i][j];
    dfs(1, 1, 8);
    if (ans == INF)
        cout << "NEVER" << endl;
    else
        cout << ans << endl;
    return 0;
}