#include <bits/stdc++.h>
using namespace std;
const int N = 25;
const int INF = 0x7FFFFFFF;
int n, m, c[N][N], vst[N], ans = INF, sum;
void dfs(int people, int work)
{
    sum += c[people][work];
    bool flag = true;
    for (int i = 0; i < m; i++)
        if (!vst[m])
        {
            flag = false;
            vst[m] = true;
            dfs(people + 1, m);
            vst[m] = false;
        }
    if (flag && people == n - 1)
        ans = min(ans, sum);
    sum -= c[people][work];
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> c[i][j];
    for (int i = 0; i < m; i++)
        dfs(0, i);
    cout << ans << endl;
    return 0;
}
