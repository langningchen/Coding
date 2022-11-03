#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull x, k;
int main()
{
    cin >> x >> k;
    for (int i = 0; i < k; i++)
    {
        x++;
        if (x % 3 == 0)
            x /= 3;
        if (x == 1)
        {
            x = (k - i - 1) % 2 + 1;
            break;
        }
    }
    cout << x << endl;
    return 0;
}