#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7FFFFFFF;
const int N = 105;
const double Err = 0.01;
int n;
double L, C, U, range, ans;
struct stop
{
    double d, p;
} s[N];
bool cmp(const stop &a, const stop &b)
{
    return a.d < b.d;
}
int Solve(int now)
{
    double minP = INF;
    int minI = N;
    double range_i = s[now].d + range + Err;
    int i;
    for (i = now + 1; s[i].d <= range_i; i++)
    {
        if (i == n + 1 || s[i].p <= s[now].p)
        {
            ans -= (C - (s[i].d - s[now].d) / U) * s[now].p;
            ans += C * s[i].p;
            return i;
        }
        if (s[i].p < minP)
            minP = s[i].p, minI = i;
    }
    if (minP == INF)
        return -1;
    ans += (s[minI].d - s[now].d) / U * minP;
    return minI;
}
int main()
{
    freopen("moon.in", "r", stdin);
    freopen("moon.out", "w", stdout);
    cin >> L >> C >> U >> s[0].p >> n;
    s[n + 1].d = L;
    for (int i = 1; i <= n; i++)
        cin >> s[i].d >> s[i].p;
    sort(s, s + n + 2, cmp);
    range = C * U;
    ans = C * s[0].p;
    int k = 0, t;
    do
    {
        t = Solve(k), k = t;
    } while (t != n + 1 && t != -1);
    if (t == -1)
        cout << -1 << endl;
    else
        cout << fixed << setprecision(2) << ans;
    return 0;
}