#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005;
const int dx[5] = {0, 0, 0, 1, -1};
const int dy[5] = {0, 1, -1, 0, 0};
ll n, x, y, ans;
bool cow[N][N];
void dfs(int x, int y)
{
    int cnt = 0, tx, ty;
    if (!cow[x][y])
        return;
    for (int i = 1; i <= 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (cow[nx][ny])
            cnt++;
        else
            tx = nx, ty = ny;
    }
    if (cnt != 3)
        return;
    cow[tx][ty] = 1;
    ans++;
    for (int i = 0; i <= 4; i++)
        dfs(tx + dx[i], ty + dy[i]);
}
int main()
{
    freopen("comfortable.in", "r", stdin);
    freopen("comfortable.out", "w", stdout);
    cin >> n;
    while (n--)
    {
        cin >> x >> y;
        x += 1000;
        y += 1000;
        if (cow[x][y])
            ans--;
        else
        {
            cow[x][y] = 1;
            for (int i = 0; i <= 4; i++)
            {
                int nx = x + dx[i], ny = y + dy[i];
                dfs(nx, ny);
            }
        }
        cout << ans << endl;
    }
    return 0;
}