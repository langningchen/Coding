#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    freopen("pure.in", "w", stdout);
    srand(time(NULL));
    ll ans = 1;
    if (rand() % 2)
    {
        for (ll i = rand() % 20 + 1; i >= 0; i--)
            ans *= 2;
        for (ll i = rand() % 20 + 1; i >= 0; i--)
            ans *= 3;
        cout << ans << endl;
        cout << "Yes" << endl;
    }
    else
    {
        ans *= rand();
        ans *= rand();
        cout << ans << endl;
        cout << "No" << endl;
    }
    return 0;
}