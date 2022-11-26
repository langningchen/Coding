#include <bits/stdc++.h>
using namespace std;
int n, a, b;
double FirstPercentage;
int main()
{
    cin >> n;
    cin >> a >> b;
    FirstPercentage = b * 1.0 / a;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        if (b * 1.0 / a - FirstPercentage > 0.05)
            cout << "better" << endl;
        else if (FirstPercentage - b * 1.0 / a > 0.05)
            cout << "worse" << endl;
        else
            cout << "same" << endl;
    }
    return 0;
}
