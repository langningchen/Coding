#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4005;
const int INF = 0x7FFFFFFF;
int n, btop, ctop, a[N][3], b[N], c[N], f[N][N];
map<int, int> Map;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 4; j++)
        {
            cin >> a[i][j];
            b[++btop] = a[i][j];
        }
    sort(b + 1, b + btop + 1);
    b[0] = -INF;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 4; j++)
            a[i][j] = Map[a[i][j]];
    for (int k = 1; k <= n; k++)
        for (int i = a[k][0]; i < a[k][2]; i++)
        {
            f[i][a[k][3]]++;
            f[i][a[k][1]]--;
        }
    for (int i = 1; i < ctop; i++)
        for (int j = 1; j < ctop; j++)
            f[i][j] += f[i][j - 1];
    ll ans;
    for (int i = 1; i < ctop; i++)
        for (int j = 1; j < ctop; j++)
            if (f[i][j])
                ans += (ll)(c[i + 1] - c[i]) * (c[j + 1] - c[j]);
    cout << ans << endl;
    return 0;
}