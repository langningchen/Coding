#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int l, r;
ll Counter;
int main()
{
    cin >> l >> r;
    for (int i = l; i <= r; i++)
    {
        int t = i;
        while (t)
        {
            if (t % 10 == 2)
                Counter++;
            t /= 10;
        }
    }
    cout << Counter << endl;
    return 0;
}