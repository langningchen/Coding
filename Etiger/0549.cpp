#include <bits/stdc++.h>
using namespace std;
int n, sum;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        sum += t;
    }
    cout << sum - n + 1 << endl;
    return 0;
}