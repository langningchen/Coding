#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 40005;
ll n, m, x[N], ans[N][4];
int main()
{
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> x[i];
    for (int a = 0; a < m; a++)
    {
        for (int b = 0; b < m; b++)
        {
            if (x[b] <= x[a])
                continue;
            for (int c = 0; c < m; c++)
            {
                if (x[c] <= x[b])
                    continue;
                for (int d = 0; d < m; d++)
                {
                    if (x[d] <= x[c])
                        continue;
                    if (2 * (x[d] - x[c]) != (x[b] - x[a]))
                        continue;
                    if (x[b] - x[a] >= (x[c] - x[b]) / 3.0)
                        continue;
                    ans[a][0]++;
                    ans[b][1]++;
                    ans[c][2]++;
                    ans[d][3]++;
                }
            }
        }
    }
    for (int i = 0; i < m; i++)
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;
    return 0;
}