#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)
{
    return !b ? a : gcd(b, a % b);
}
int main()
{
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}
