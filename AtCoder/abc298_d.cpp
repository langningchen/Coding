#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const ll MOD_LENGTH = log10(MOD) + 1;
ll mod(string a)
{
    while (a.size() > MOD_LENGTH)
    {
        ll TempModLength = MOD_LENGTH + (a.substr(0, MOD_LENGTH) <= std::to_string(MOD));
        a = std::to_string(atoll(a.substr(0, TempModLength).c_str()) % MOD) + a.substr(TempModLength);
    }
    return atoll(a.c_str()) % MOD;
}
ll q;
string s = "1";
int main()
{
    cin >> q;
    for (ll i = 0; i < q; i++)
    {
        ll o, x;
        cin >> o;
        if (o == 1)
        {
            cin >> x;
            s.push_back('0' + x);
        }
        else if (o == 2)
            s.erase(0, 1);
        else
            cout << mod(s) << endl;
    }
    return 0;
}
