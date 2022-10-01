#include <bits/stdc++.h>
using namespace std;
int a, b;
int gcd(int a, int b)
{
    return !b ? a : gcd(b, a % b);
}
int main()
{
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}
