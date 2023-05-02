#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll a, b, ans;
bool flag;
int main()
{
    freopen("digit.in", "r", stdin);
    freopen("digit.out", "w", stdout);
    cin >> a >> b;
    ans = a + b;
    string Temp;
    ll Count = 0;
    if (ans < 0)
    {
        flag = true;
        ans = -ans;
    }
    while (ans)
    {
        if (Count >= 3)
        {
            Temp.push_back(',');
            Count = 0;
        }
        Temp.push_back(ans % 10 + '0');
        ans /= 10;
        Count++;
    }
    if (flag)
        cout << "-";
    for (ll i = Temp.size() - 1; i >= 0; i--)
        cout << Temp[i];
    cout << endl;
    return 0;
}