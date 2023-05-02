#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main()
{
    freopen("pure.in", "r", stdin);
    freopen("pure.out", "w", stdout);
    cin >> n;
    if (n % 2 != 0 || n % 3 != 0)
        cout << "No" << endl;
    else
    {
        while (n % 2 == 0)
            n /= 2;
        while (n % 3 == 0)
            n /= 3;
        if (n == 1)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}