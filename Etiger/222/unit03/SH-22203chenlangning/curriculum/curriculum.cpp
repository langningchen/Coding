#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, k, s[N], c[N], ans_a, ans_b;
double ans;
bool t[N];
ll gcd(ll a, ll b)
{ // puzzle 2210 curriculum 2194 income 3080 three 2741
    return b == 0 ? a : gcd(b, a % b);
}
void dfs(int x, int t)
{
    if (x == n)
    {
        if (t == 0)
        {
            ll now_a = 0;
            ll now_b = 0;
            for (int i = 0; i < n; i++)
            {
                if (t[i])
                {
                    now_a += s[i] * c[i];
                    now_b += c[i];
                }
            }
            cout << endl;
        }
        return 0;
    }
    dfs(x + 1, t);
    t[x] = true;
    dfs(x + 1, t - 1);
    t[x] = false;
}
void SolveK1()
{
    ll sum_a = 0;
    ll sum_b = 0;
    for (int i = 0; i < n; i++)
    {
        sum_a += s[i] * c[i];
        sum_b += c[i];
    }
    ll ans = 0;
    ll ans_a = 0;
    ll ans_b = 0;
    for (int i = 0; i < n; i++)
    {
        ll a = sum_a - s[i] * c[i], b = sum_b - c[i];
        if (a * 1.0 / b > ans)
        {
            ans = a * 1.0 / b;
            ans_a = a;
            ans_b = b;
        }
    }
    ll tmp = gcd(ans_a, ans_b);
    ans_a /= tmp;
    ans_b /= tmp;
    cout << ans_a << "/" << ans_b << endl;
}
int main()
{
    freopen("curriculum.in", "r", stdin);
    freopen("curriculum.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> s[i] >> c[i];
    if (k == 1)
        SolveK1();
    else
    {
        dfs(0, k);
        ll tmp = gcd(ans_a, ans_b);
        ans_a /= tmp;
        ans_b /= tmp;
        cout << ans_a << "/" << ans_b << endl;
    }
    return 0;
}
