#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 360;
const int INF = 0x7FFF'FFFF;
ll n, m, c1, c2, d;
ll sx, sy, tx, ty;
string s;
ll a[N][N], flag[N][N];
bool v[N][N][16][16];
void add(ll i, ll j, ll x)
{
    for (ll d = -x + 1; d <= x - 1; d++)
    {
        int now_i = i + d;
        if (now_i < 1 || now_i > n)
            continue;
        ll p = x - 1 - abs(d);
        int start_j = j - p;
        if (start_j < 1)
            a[now_i][0] += 1;
        else
            a[now_i][start_j] += 1;
        int end_j = j + p + 1;
        if (end_j <= m)
            a[now_i][end_j] -= 1;
    }
}
struct info
{
    ll x, y, u1, u2, t;
};
ll ans = INF, ans1 = INF, ans2 = INF;
ll dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
ll dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
void bfs()
{
    queue<info> q;
    q.push((info){sx, sy, 0, 0, 0});
    v[sx][sy][0][0] = 1;
    while (!q.empty())
    {
        info now = q.front();
        q.pop();
        if (now.t > ans)
            continue;
        if (now.x == tx && now.y == ty)
        {
            if (now.t < ans)
            {
                ans = now.t;
                ans1 = now.u1;
                ans2 = now.u2;
            }
            else
            {
                if (ans1 + ans2 > now.u1 + now.u2)
                {
                    ans1 = now.u1;
                    ans2 = now.u2;
                }
                else if (ans1 + ans2 == now.u1 + now.u2 && ans1 > now.u1)
                {
                    ans1 = now.u1;
                    ans2 = now.u2;
                }
            }
            continue;
        }
        for (ll i = 0; i < 8; i++)
        {
            ll nx = now.x + dx[i];
            ll ny = now.y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m)
                continue;
            if (flag[nx][ny] == 1)
                continue;
            if (a[nx][ny] <= 0 && v[nx][ny][now.u1][now.u2] == 0)
            {
                v[nx][ny][now.u1][now.u2] = 1;
                q.push((info){nx, ny, now.u1, now.u2, now.t + 1});
            }
            else if (now.u1 < c1 && v[nx][ny][now.u1 + 1][now.u2] == 0)
            {
                v[nx][ny][now.u1 + 1][now.u2] = 1;
                q.push((info){nx, ny, now.u1 + 1, now.u2, now.t + 1});
            }
        }
        if (now.u2 + 1 > c2)
            continue;
        for (ll i = 0; i < 4; i++)
        {
            ll nx = now.x + dx[i] * d;
            ll ny = now.y + dy[i] * d;
            if (nx < 1 || nx > n || ny < 1 || ny > m)
                continue;
            if (flag[nx][ny] == 1)
                continue;
            if (a[nx][ny] <= 0 && v[nx][ny][now.u1][now.u2 + 1] == 0)
            {
                v[nx][ny][now.u1][now.u2 + 1] = 1;
                q.push((info){nx, ny, now.u1, now.u2 + 1, now.t + 1});
            }
            else if (now.u1 < c1 && v[nx][ny][now.u1 + 1][now.u2 + 1] == 0)
            {
                v[nx][ny][now.u1 + 1][now.u2 + 1] = 1;
                q.push((info){nx, ny, now.u1 + 1, now.u2 + 1, now.t + 1});
            }
        }
    }
}
int main()
{
    freopen("steal.in", "r", stdin);
    freopen("steal.out", "w", stdout);
    cin >> n >> m >> c1 >> c2 >> d;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            cin >> s;
            if (s == "S")
                flag[i][j] = -2, sx = i, sy = j;
            else if (s == "T")
                flag[i][j] = -1, tx = i, ty = j;
            else if (s == ".")
                ;
            else
            {
                flag[i][j] = 1;
                ll x = s[0] - '0';
                for (unsigned long long k = 1; k < s.size(); k++)
                    x = x * 10 + s[k] - '0';
                add(i, j, x);
            }
        }
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            a[i][j] += a[i][j - 1];
    bfs();
    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << " " << ans1 << " " << ans2 << endl;
    return 0;
}
