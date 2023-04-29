#include <bits/stdc++.h>
using namespace std;
int n, k, i;
int main()
{
    cin >> n >> k;
    if (n % 19 != 0)
    {
        cout << "NO" << endl;
        return 0;
    }
    while (n > 0)
    {
        if (n % 10 == 3)
            i++;
        n /= 10;
    }
    if (i != k)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    return 0;
}
