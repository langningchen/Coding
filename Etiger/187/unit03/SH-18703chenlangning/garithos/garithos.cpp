#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll n, x[N], y[N];
ll GetLength(ll a, ll b)
{
    return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}
ll FindLongest(ll Start, ll Exclude = -1)
{
    ll Answer = 0, MaxValue = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == Start || i == Exclude)
            continue;
        ll ThisValue = GetLength(i, Start);
        if (ThisValue > MaxValue)
        {
            MaxValue = ThisValue;
            Answer = i;
        }
    }
    return Answer;
}
void Solve0()
{
    ll ans;
    // ll ansa, ansb, ansc;
    for (ll a = 0; a < n; a++)
        for (ll b = 0; b < n; b++)
            for (ll c = 0; c < n; c++)
                if (GetLength(a, b) + GetLength(b, c) + GetLength(c, a) > ans)
                {
                    ans = GetLength(a, b) + GetLength(b, c) + GetLength(c, a);
                    // ansa = a;
                    // ansb = b;
                    // ansc = c;
                }
    cout << ans << endl;
    // cout << ansa << " " << ansb << " " << ansc << endl;
}
void Solve1()
{
    ll ans = 0;
    // ll ansa, ansb, ansc;
    for (int i = 0; i < n; i++)
    {
        ll a = (i);
        ll b = FindLongest(a);
        ll c = FindLongest(b, a);
        // cout << GetLength(a, b) + GetLength(b, c) + GetLength(c, a) << " " << a << " " << b << " " << c << endl;
        if (GetLength(a, b) + GetLength(b, c) + GetLength(c, a) > ans)
        {
            ans = GetLength(a, b) + GetLength(b, c) + GetLength(c, a);
            // ansa = a;
            // ansb = b;
            // ansc = c;
        }
    }
    // cout << endl;
    cout << ans << endl;
}
void Solve2()
{
    ll a = FindLongest(0);
    ll b = FindLongest(a);
    ll c = FindLongest(b, a);
    cout << GetLength(a, b) + GetLength(b, c) + GetLength(c, a) << endl;
    // cout << a << " " << b << " " << c << endl;
}
int main()
{
    freopen("garithos.in", "r", stdin);
    freopen("garithos.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    if (n <= 400)
        Solve0();
    else if (n <= 7500)
        Solve1();
    else
        Solve2();
    return 0;
}