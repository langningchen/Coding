#include <bits/stdc++.h>
using namespace std;
double ans1, ans2;
int main()
{
    cin >> ans2;
    ans1 = ans2;
    for (int i = 0; i < 9; i++)
    {
        ans1 += ans2;
        ans2 /= 2;
    }
    cout << ans1 << endl
         << ans2 / 2 << endl;
    return 0;
}
