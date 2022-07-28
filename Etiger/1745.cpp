#include <bits/stdc++.h>
using namespace std;
int T, n;
int main()
{
    // freopen("stomach.in", "r", stdin);
    // freopen("stomach.out", "w", stdout);
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> n;
        int x, sg = 0;
        for (int j = 0; j < n; j++)
        {
            cin >> x;
            sg ^= (x % 4 == 3 ? x + 1 : (x % 4 == 0 ? x - 1 : x));
        }
        if (sg == 0)
            cout << "LOSE" << endl;
        else
            cout << "WIN" << endl;
    }
    return 0;
}