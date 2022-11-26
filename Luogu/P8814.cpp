#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k, n, e, d, c;
bool founded;
int main()
{
    // freopen("P8814.in", "r", stdin);
    // freopen("P8814.out", "w", stdout);
    // freopen("P8814.log", "w", stderr);
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        founded = false;
        cin >> n >> e >> d;
        c = n + 2 - e * d;
        for (ll p = 1; p * p < n; p++)
        {
            if (n % p == 0)
            {
                ll q = n / p;
                // cerr << "p = " << p << " q = " << q << endl;
                if (p + q == c)
                {
                    cout << p << " " << q << endl;
                    founded = true;
                }
            }
        }
        if (!founded)
            cout << "NO" << endl;
    }
    return 0;
}