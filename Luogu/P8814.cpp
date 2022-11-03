#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k, n, e, d, c;
bool founded;
int main()
{
    // freopen("decode.in", "r", stdin);
    // freopen("decode.out", "w", stdout);
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