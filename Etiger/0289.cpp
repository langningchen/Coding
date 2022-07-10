#include <bits/stdc++.h>
using namespace std;
int main()
{
    multiset<string> ms;
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (ms.count(s))
        {
            ans++;
            ms.erase(s);
        }
        else
            ms.insert(s);
    }
    cout << ans << endl;
    return 0;
}
