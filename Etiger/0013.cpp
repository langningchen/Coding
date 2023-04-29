#include <bits/stdc++.h>
using namespace std;
const int N = 3;
char c[N], o[N];
int main()
{
    freopen("ceasar.in", "r", stdin);
    freopen("ceasar.out", "w", stdout);
    cin >> c[0] >> c[1] >> c[2];
    for (int i = 0; i < 3; i++)
    {
        o[i] = (c[i] - 'a' + 1) % 26 + 'a';
    }
    cout << o[0] << " " << o[1] << " " << o[2] << endl;
    return 0;
}
