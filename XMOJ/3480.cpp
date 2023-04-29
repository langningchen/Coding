// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const ll N = 1 << 8 + 5;
// ll n, a[N], Answer;
// ll LowBit(ll x)
// {
//     return x & (-x);
// }
// int main()
// {
//     // freopen("f.in", "r", stdin);
//     // freopen("f.out", "w", stdout);
//     scanf("%lld", &n);
//     n = pow(2, n);
//     for (ll i = 0; i < n; i++)
//         scanf("%lld", &a[i]);
//     sort(a, a + n);
//     for (ll k = 1; k < n; k++)
//     {
//         Answer = 0;
//         for (ll x = 1; x <= k; x++)
//         {
//             cout << x << " " << x - LowBit(x) << endl;
//             Answer = max(Answer, a[x] + a[x - LowBit(x)]);
//         }
//         printf("%lld\n", Answer);
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1 << 8 + 5;
ll n;
struct node
{
    ll x, y;
} b[N];
int main()
{
    cin >> n;
    n = pow(2, n);
    for (int i = 0; i < n; i++)
        cin >> b[i].x;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1 << n); j++)
            if (j & (1 << i))
                b[j].y = max(min(b[j].x, b[j ^ (1 << i)].x), max(b[j].y, b[j ^ (1 << i)].y)),
                b[j].x = max(b[j].x, b[j ^ (1 << i)].x);
    for (int i = 1; i < n; i++)
        cout << b[i].y << endl;
    return 0;
}
