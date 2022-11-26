#include <bits/stdc++.h>
using namespace std;
int n, ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s[3] - s[0] - s[1] - s[2] > -'0' - '0')
            ans++;
    }
    cout << ans << endl;
    return 0;
}