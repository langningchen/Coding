#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 10005;
ll n, k, a[N], Answer;
void Input()
{
    scanf("%lld%lld", &n, &k);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
}
void SolveK1()
{
    for (ll i = 1; i <= n; i++)
        Answer += (a[i] != 1);
    cout << Answer << endl;
}
int main()
{
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
    Input();
    if (k == 1)
        SolveK1();
    return 0;
}
