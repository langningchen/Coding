#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll ans;
bool Related7(int x)
{
    if (x % 7 == 0)
        return true;
    string tmp = to_string(x);
    if (tmp.find("7") != string::npos)
        return true;
    return false;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        if (!Related7(i))
            ans += i * i;
    cout << ans << endl;
    return 0;
}