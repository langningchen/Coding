#include <bits/stdc++.h>
using namespace std;
set<string> s;
string a, b;
int main()
{
    freopen("aimaya.in", "r", stdin);
    freopen("aimaya.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a >> b;
        s.insert(a);
    }
    cin >> a >> b;
    if (s.count(a))
        cout << "No" << endl;
    else
        cout << "Yes" << endl;
    return 0;
}
