#include <bits/stdc++.h>
using namespace std;
const int N = 505;
typedef long long ll;
const ll nDigits = 10;
const ll U = 1e10;
const ll SZ = 105;
typedef ll BigNum[SZ];
ll n, m, k, X[N], A[N], B[N];
void convert(ll *a, ll s)
{
    ll i;
    for (i = 0; i < SZ && s; i++)
        a[i] = s % U, s /= U;
    for (; i < SZ; i++)
        a[i] = 0;
}
void copy(ll *a, ll *b)
{
    for (ll i = 0; i < SZ; i++)
        a[i] = b[i];
}
bool eq0(ll *a)
{
    for (ll i = 0; i < SZ; i++)
        if (a[i])
            return 0;
    return 1;
}
void print(ll *a)
{
    ll i;
    for (i = SZ - 1; i > 0; i--)
        if (a[i])
            break;
    cout << a[i--];
    for (; i >= 0; i--)
        cout << setw(nDigits) << setfill('0') << a[i];
    cout << endl;
}
void add(ll *a, ll *b)
{
    for (ll i = 0; i < SZ; i++)
        if ((a[i] += b[i]) >= U)
        {
            a[i + 1]++;
            a[i] -= U;
        }
}
void mul(ll *a, ll b)
{
    for (ll i = 0, c = 0; i < SZ; i++)
    {
        c = c / U + a[i] * b;
        a[i] = c % U;
    }
}
void solve1()
{
    cout << k << endl;
    cout << (1 + k) * k / 2 << endl;
}
void solveSmallNum()
{
    ll a = 1;
    for (ll i = 1; i <= n - 1; i++)
        a *= k;
    ll cnt = a;
    cnt *= k;
    ll b = k * (k + 1) / 2;
    a *= b;
    ll sum = 0;
    for (ll i = 0; i < n; i++)
    {
        sum += a;
        a *= 10;
    }
    cout << cnt << endl;
    cout << sum << endl;
}
void solveBigNum()
{
    BigNum a, cnt, sum;
    convert(a, 1);
    for (int i = 1; i < n; i++)
        mul(a, k);
    copy(cnt, a);
    mul(cnt, k);
    int b = k * (k + 1) / 2;
    mul(a, b);
    convert(sum, 0);
    for (ll i = 0; i < n; i++)
    {
        add(sum, a);
        mul(a, 10);
    }
    print(cnt);
    print(sum);
}
ll cnt[N][512], sum[N][512];
void solveSmallNumAB()
{
    for (int i = 1; i <= m; i++)
        X[B[i]] |= (1 << A[i] - 1);
    int nPtn = (1 << k);
    cnt[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int p = 0; p < nPtn; p++)
        {
            if (cnt[i][p] == 0)
                continue;
            for (int a = 1; a <= k; a++)
            {
                if (p & X[a])
                    continue;
                cnt[i + 1][p | (1 << a - 1)] += cnt[i][p];
                sum[i + 1][p | (1 << a - 1)] += sum[i][p] * 10 + a * cnt[i][p];
            }
        }
    ll C = 0, S = 0;
    for (int p = 0; p < nPtn; p++)
    {
        C += cnt[n][p];
        S += sum[n][p];
    }
    cout << C << endl;
    cout << S << endl;
}
BigNum c[2][512], s[2][512], C, S;
void solveBigNumAB()
{
    for (int i = 1; i <= m; i++)
        X[B[i]] |= (1 << A[i] - 1);
    int nPtn = (1 << k);
    convert(c[0][0], 1);
    for (int i = 0; i < n; i++)
    {
        for (int p = 0; p < nPtn; p++)
            convert(c[i & 1 ^ 1][p], 0), convert(s[i & 1 ^ 1][p], 0);
        for (int p = 0; p < nPtn; p++)
        {
            if (eq0(c[i & 1][p]))
                continue;
            mul(s[i & 1][p], 10);
            for (int a = 1; a <= k; a++)
            {
                add(s[i & 1][p], c[i & 1][p]);
                if (p & X[a])
                    continue;
                add(c[i & 1 ^ 1][p | (1 << a - 1)], c[i & 1][p]);
                add(s[i & 1 ^ 1][p | (1 << a - 1)], s[i & 1][p]);
            }
        }
    }
    convert(C, 0);
    convert(S, 0);
    for (int p = 0; p < nPtn; p++)
    {
        add(C, c[n & 1][p]);
        add(S, s[n & 1][p]);
    }
    print(C);
    print(S);
}
int main()
{
    freopen("word.in", "r", stdin);
    freopen("word.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
        cin >> A[i] >> B[i];
    if (n == 1)
        solve1();
    else if (m == 9 && n <= 9)
        solveSmallNum();
    else if (m == 0)
        solveBigNum();
    else if (n <= 9)
        solveSmallNumAB();
    else
        solveBigNumAB();
    return 0;
}