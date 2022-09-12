#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, a[N], Counter;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                Counter++;
            }
    }
    cout << Counter << endl;
    return 0;
}