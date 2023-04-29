#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55;
ll n, k[N];
int main()
{
    cin >> n;
    k[0] = 1;
    for (ll i = 1; i < n; i++)
        k[i] = k[i - 1] * 2 + 1;
    cout << k[n - 1];
    return 0;
}
