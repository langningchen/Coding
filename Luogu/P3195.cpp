#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double ld;
const ll N = 50005;
ll n, L, Head = 1, Tail = 1, Queue[N];
ld C[N], f[N];
ld a(ll i) { return C[i] + i; }
ld b(ll i) { return a(i) + L + 1; }
ld X(ll i) { return b(i); }
ld Y(ll i) { return f[i] + pow(b(i), 2); }
ld Distance(ll i, ll j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }
int main()
{
    scanf("%lld%lld", &n, &L);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lf", &C[i]);
        C[i] += C[i - 1];
    }
    for (ll i = 1; i <= n; i++)
    {
        while (Head < Tail && Distance(Queue[Head], Queue[Head + 1]) < 2 * a(i))
            Head++;
        f[i] = f[Queue[Head]] + pow(a(i) - b(Queue[Head]), 2);
        while (Head < Tail && Distance(i, Queue[Tail - 1]) < Distance(Queue[Tail - 1], Queue[Tail]))
            Tail--;
        Tail++;
        Queue[Tail] = i;
    }
    printf("%lld\n", (ll)f[n]);
    return 0;
}
