// #include <bits/stdc++.h>
// using namespace std;
// typedef unsigned long long ull;
// const ull MOD = 10007;
// const ull N = 100005;
// ull n, m, ans, a[N], b[N], s1[N][2], s2[N][2];
// int main()
// {
//     ios::sync_with_stdio(false);
//     cin >> n >> m;
//     for (ull i = 1; i <= n; i++)
//         cin >> a[i];
//     for (ull i = 1; i <= n; i++)
//     {
//         cin >> b[i];
//         s1[b[i]][i % 2]++;
//         s2[b[i]][i % 2] = (s2[b[i]][i % 2] + a[i]) % MOD;
//     }
//     for (ull i = 1; i <= n; i++)
//         ans = (ans + i * ((s2[b[i]][i % 2] - a[i]) + a[i] * (s1[b[i]][i % 2] - 1) % MOD) % MOD) % MOD;
//     cout << ans << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int r = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        r = (r << 1) + (r << 3) + (c ^ '0'), c = getchar();
    return r * f;
}
int a[100005] = {0};
int b[100005] = {0};
int s[100005][2] = {0};
int summ[100005][2] = {0};
int main()
{
    int n = read(), m = read(), sum = 0;
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= n; ++i)
        b[i] = read();
    for (int i = 1; i <= n; ++i)
        s[b[i]][i % 2]++, summ[b[i]][i % 2] = (summ[b[i]][i % 2] + a[i]) % 10007;
    for (int i = 1; i <= n; ++i)
        sum = (sum + (i * (summ[b[i]][i % 2] - a[i]) + (s[b[i]][i % 2] - 1) * a[i] * i) % 10007) % 10007;
    cout << sum % 10007;
    return 0;
}