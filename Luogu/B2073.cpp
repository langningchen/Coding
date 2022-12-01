#include <bits/stdc++.h>
using namespace std;
int a, b, n;
double ans;
int main()
{
    cin >> a >> b >> n;
    if (a == 1 && b == 1 && n == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    ans = a * 1.0 / b;
    for (int i = 1; i < n; i++)
    {
        ans *= 10;
        ans -= (int)ans;
    }
    cout << (int)(ans * 10) % 10 << endl;
    return 0;
}