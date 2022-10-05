#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    freopen("week.in", "r", stdin);
    freopen("week.out", "w", stdout);
    string w[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int year, month, day;
    cin >> year >> month >> day;
    if (month < 3)
    {
        month += 12;
        year--;
    }
    int c = year / 100;
    year %= 100;
    int D = c / 4 - 2 * c + year + year / 4;
    D += 13 * (month + 1) / 5 + day - 1 + 210;
    cout << w[D % 7] << endl;
    return 0;
}