#include <bits/stdc++.h>
using namespace std;
int m;
int main()
{
    cin >> m;
    if (m % 4 != 1)
        cout << -1 << endl;
    else
    {
        for (int i = 0; i < m / 4; i++)
            cout << "0011";
        cout << "0";
    }
    return 0;
}