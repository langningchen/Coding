#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
int Open[N], n;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double a;
        int t;
        cin >> a >> t;
        for (int j = 1; j <= t; j++)
            Open[(int)floor(a * j)] ^= 1;
    }
    int i = 1;
    while (1)
    {
        if (Open[i])
        {
            cout << i << endl;
            break;
        }
        i++;
    }
    return 0;
}