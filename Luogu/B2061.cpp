#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k, ans1, ans2, ans3;
int main()
{
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        ll t;
        cin >> t;
        if (t == 1)
            ans1++;
        if (t == 5)
            ans2++;
        if (t == 10)
            ans3++;
    }
    cout << ans1 << endl
         << ans2 << endl
         << ans3 << endl;
    return 0;
}