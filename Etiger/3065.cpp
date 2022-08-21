#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string to_string2(ll a)
{
    if (a == 0)
        return "0";
    bool flag = false;
    string ans = "";
    if (a < 0)
    {
        flag = true;
        a = -a;
    }
    while (a)
    {
        ans += (a % 10 + '0');
        a /= 10;
    }
    reverse(ans.begin(), ans.end());
    if (flag)
        ans = "-" + ans;
    return ans;
}
int main()
{
    freopen("digit.in", "r", stdin);
    freopen("digit.out", "w", stdout);
    ll a, b;
    cin >> a >> b;
    string s = to_string2(a + b);
    for (int i = s.size() - 3; i >= 0; i -= 3)
        if (i >= 1 && s[i - 1] != '-')
            s.insert(i, ",");
    cout << s << endl;
    return 0;
}