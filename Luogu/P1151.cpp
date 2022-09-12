#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int k, Found = false;
int main()
{
    cin >> k;
    for (int i = 10000; i <= 30000; i++)
        if (((i % 100000) / 100) % k == 0 &&
            ((i % 10000) / 10) % k == 0 &&
            ((i % 1000) / 1) % k == 0)
        {
            Found = true;
            cout << i << endl;
        }
    if (!Found)
        cout << "No" << endl;
    return 0;
}