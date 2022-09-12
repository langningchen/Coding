#include <bits/stdc++.h>
using namespace std;
void I2S(int x, string &str)
{
    stringstream ss;
    if (x <= 9)
        ss << 0;
    ss << x;
    ss >> str;
}
int nDays[13] = {0,
                 31, 29, 31, 30,
                 31, 30, 31, 31,
                 30, 31, 30, 31};
int main()
{
    freopen("date.in", "r", stdin);
    freopen("date.out", "w", stdout);
    string date1, date2;
    cin >> date1 >> date2;
    int ans = 0;
    for (int m = 1; m <= 12; m++)
    {
        string month;
        I2S(m, month);
        for (int d = 1; d <= nDays[m]; d++)
        {
            string day;
            I2S(d, day);
            string md = month + day;
            string year = md;
            reverse(year.begin(), year.end());
            string date = year + md;
            if (date >= date1 && date <= date2)
                ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
