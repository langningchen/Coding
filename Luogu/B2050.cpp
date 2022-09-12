#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int main()
{
    cin >> a >> b >> c;
    if (a + b > c && b + c > a && c + a > b)
        cout << 1 << endl;
    else
        cout << 0 << endl;
    return 0;
}