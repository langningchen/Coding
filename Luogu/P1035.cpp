#include <bits/stdc++.h>
using namespace std;
int n, k;
double s;
int main()
{
    cin >> k;
    while (s <= k)
    {
        n++;
        s += 1.0 / n;
    }
    cout << n << endl;
    return 0;
}