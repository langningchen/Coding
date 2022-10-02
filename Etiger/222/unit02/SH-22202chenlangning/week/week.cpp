#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll y, m, d, ans;
string Name[7] = {"Sunday",
                  "Monday",
                  "Tuesday",
                  "Wednesday",
                  "Thursday",
                  "Friday",
                  "Saturday"};
short Months[12] = {3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3};
bool IsLunarYear(ll y)
{
    if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
    {
        return true;
    }
    return false;
}
int main()
{
    freopen("week.in", "r", stdin);
    freopen("week.out", "w", stdout);
    ans = 5;
    cin >> y >> m >> d;
    for (int i = 1971; i < y; i++)
    {
        ans = (ans + 1) % 7;
        if (IsLunarYear(i))
            ans = (ans + 1) % 7;
    }
    for (int i = 1; i < m; i++)
    {
        ans = (ans + Months[i - 1]) % 7;
    }
    ans = (ans + d - 1) % 7;
    cout << Name[ans] << endl;
    return 0;
}