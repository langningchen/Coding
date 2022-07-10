#include <bits/stdc++.h>
using namespace std;
double s, k;
int n = 1;
int main()
{
    cin >> k;
    while (s <= k)
    {
        s += 1.0 / n;
        n++;
    }
    cout << n - 1 << endl;
    return 0;
}
