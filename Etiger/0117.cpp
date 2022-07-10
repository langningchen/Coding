#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll h(ll k)
{
    return k < 2 ? 1 : h(k - 1) * (4 * k - 2) / (k + 1);
}
int main()
{
    int n;
    cin >> n;
    cout << h(n);
    return 0;
}
