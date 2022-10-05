#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, x[N], y[N], ans, ansa, ansb, ansc;
bool vst[N];
int main()
{
    freopen("garithos.in", "r", stdin);
    freopen("garithos_BF.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    for (int a = 0; a < n; a++)
        for (int b = 0; b < n; b++)
            for (int c = 0; c < n; c++)
            {
                if (abs(x[a] - x[b]) + abs(y[a] - y[b]) + abs(x[b] - x[c]) + abs(y[b] - y[c]) + abs(x[c] - x[a]) + abs(y[c] - y[a]) > ans)
                {
                    ans = abs(x[a] - x[b]) + abs(y[a] - y[b]) + abs(x[b] - x[c]) + abs(y[b] - y[c]) + abs(x[c] - x[a]) + abs(y[c] - y[a]);
                    ansa = a;
                    ansb = b;
                    ansc = c;
                }
            }
    cout << ans << endl;
    cout << ansa << " " << ansb << " " << ansc << endl;
    return 0;
}