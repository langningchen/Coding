#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 505;
int n, m, T;
struct Node
{
    int t, s;
} Me[N], Other[M];
bool cmpt(const Node cmp1, const Node cmp2) { return cmp1.t < cmp2.t; }
bool cmps(const Node cmp1, const Node cmp2) { return cmp1.s < cmp2.s; }
int main()
{
    cin >> n >> m >> T;
    for (int i = 0; i < n; i++)
        cin >> Me[i].t >> Me[i].s;
    for (int i = 0; i < m; i++)
        cin >> Other[i].t >> Other[i].s;
    sort(Me, Me + n, cmpt);
    sort(Other, Other + m, cmps);
    int t = 0, sc = 0, zuochulaitimu = 0;
    for (int i = 0; i < n; i++)
    {
        zuochulaitimu = i;
        if (t + Me[i].t > T)
            break;
        t += Me[i].t;
        sc += Me[i].s;
    }
    int ans = m + 1;
    for (int i = 0; i < m; i++)
        if (sc > Other[i].s)
            ans--;
    // cout << ans << "   finished: " << zuochulaitimu << "   score: " << sc << "   time: " << t << endl;
    sort(Other, Other + m, cmpt);
    for (int i = m - ans + 1; i < m; i++)
    {
        if (sc > Other[i].s)
            continue;
        while (zuochulaitimu > 0)
        {
            if (t + Other[i].t <= T)
            {
                t += Other[i].t;
                if (sc > Other[i].s)
                {
                    // cout << "Hacked " << Other[i].t << " " << Other[i].s << endl;
                    ans--;
                }
                break;
            }
            zuochulaitimu--;
            t -= Me[zuochulaitimu].t;
            sc -= Me[zuochulaitimu].s;
            // cout << ans << "   finished: " << zuochulaitimu << "   score: " << sc << "   time: " << t << "    Other[i].t=" << Other[i].t << endl;
        }
    }
    cout << ans << endl;
    return 0;
}