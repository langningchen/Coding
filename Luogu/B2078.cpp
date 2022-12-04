#include <bits/stdc++.h>
using namespace std;
string m;
int k;
int main()
{
    cin >> m >> k;
    for (size_t i = 0; i < m.size(); i++)
        if (m[i] == '3')
            k--;
    if (k == 0)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}