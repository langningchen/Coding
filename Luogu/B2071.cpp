#include <bits/stdc++.h>
using namespace std;
int a, b, c, ans = 2;
int main()
{
    cin >> a >> b >> c;
    while (1)
    {
        if (a % ans == b % ans && b % ans == c % ans)
            break;
        ans++;
    }
    cout << ans << endl;
    return 0;
}