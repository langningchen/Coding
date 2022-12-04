#include <bits/stdc++.h>
using namespace std;
const string Name[7] = {"Sunday",
                        "Monday",
                        "Tuesday",
                        "Wednesday",
                        "Thursday",
                        "Friday",
                        "Saturday"};
int a, b, ans = 1;
int main()
{
    cin >> a >> b;
    a %= 7;
    for (int i = 0; i < b; i++)
        ans = ans * a % 7;
    cout << Name[ans] << endl;
    return 0;
}
