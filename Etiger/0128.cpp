#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll f(ll x)
{
    return x == 1 ? 1 : x * x + f(x - 1);
}
int main()
{
    cin >> n;
    cout << f(n) << endl;
    return 0;
}
