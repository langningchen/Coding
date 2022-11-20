// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// const int N = 50005;
// int n, H, q[N];
// struct Line
// {
//     ld b, k;
// } lines[N];
// ld t[N], f[N];
// ld X(ll u, ll v)
// {
//     return (lines[u].b - lines[v].b) / (lines[u].k - lines[v].k);
// }
// int main()
// {
//     freopen("packing.in", "r", stdin);
//     freopen("packing.out", "w", stdout);
//     cin >> n >> H;
//     H++;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> t[i];
//         t[i] += t[i - 1];
//     }
//     for (int i = 1; i <= n; i++)
//         t[i] += i;
//     int l = 1, r = 2;
//     for (int i = 1; i <= n; i++)
//     {
//         while (r - l >= 2 && X(q[l], q[l + 1]) < 2 * t[i])
//             l++;
//         ll j = q[l];
//         f[i] = f[j] + (t[i] - t[j] - H) * (t[i] - t[j] - H);
//         lines[i] = (Line){f[i] + t[i] * t[i] + 2 * H * t[i], t[i]};
//         while (r - l >= 2 && X(i, q[r - 1]) < X(q[r - 1], q[r - 2]))
//             r--;
//         q[r++] = i;
//     }
//     cout << f[n] << endl;
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long LL;
const int maxn = 50010;
int n, L;
db sum[maxn], dp[maxn];
int head, tail, Q[maxn];
inline db a(int i) { return sum[i] + i; }
inline db b(int i) { return a(i) + L + 1; }
inline db X(int i) { return b(i); }
inline db Y(int i) { return dp[i] + b(i) * b(i); }
inline db slope(int i, int j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }
int main()
{
    freopen("packing.in", "r", stdin);
    freopen("packing.out", "w", stdout);
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &sum[i]);
        sum[i] += sum[i - 1];
    }
    head = tail = 1;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slope(Q[head], Q[head + 1]) < 2 * a(i))
            ++head;
        dp[i] = dp[Q[head]] + (a(i) - b(Q[head])) * (a(i) - b(Q[head]));
        while (head < tail && slope(i, Q[tail - 1]) < slope(Q[tail - 1], Q[tail]))
            --tail;
        Q[++tail] = i;
    }
    printf("%lld\n", (LL)dp[n]);
    return 0;
}
