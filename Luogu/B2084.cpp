#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main()
{
    cin >> n;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0)
        {
            cout << n / i << endl;
            break;
        }
    return 0;
}
