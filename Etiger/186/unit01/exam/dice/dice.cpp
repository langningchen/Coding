#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T;
int main()
{
    freopen("dice.in", "r", stdin);
    freopen("dice.out", "w", stdout);
    cin >> T;
    for (ll i = 0; i < T; i++)
    {
        ll a1, a2, a3, a4, b1, b2, b3, b4;
        cin >> a1 >> a2 >> a3 >> a4 >> b1 >> b2 >> b3 >> b4;
        if (((min(min(a1, a2), min(a3, a4)) < max(max(b1, b2), max(b3, b4))) && max(max(a1, a2), max(a3, a4)) - min(min(b1, b2), min(b3, b4)) > 1) ||
            ((max(max(a1, a2), max(a3, a4)) < min(min(b1, b2), min(b3, b4))) && min(min(a1, a2), min(a3, a4)) - max(max(b1, b2), max(b3, b4)) > 1))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}