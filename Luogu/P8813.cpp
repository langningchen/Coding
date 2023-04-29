#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int main()
{
    cin >> a >> b;
    c = pow(a, b);
    if (c < 0)
        cout << -1 << endl;
    else
        cout << c << endl;
    return 0;
}