#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, a, b, c;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll t;
        cin >> t;
        a += t;
        cin >> t;
        b += t;
        cin >> t;
        c += t;
    }
    cout << a << " " << b << " " << c << " " << a + b + c << endl;
    return 0;
}
