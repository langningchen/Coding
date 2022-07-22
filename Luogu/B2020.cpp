#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int a[N], eat;
int main()
{
    for (int i = 0; i < 5; i++)
        cin >> a[i];
    for (int i = 0; i < 5; i++)
    {
        eat += a[i] % 3;
        a[i == 0 ? 4 : i - 1] += a[i] / 3;
        a[i == 4 ? 0 : i + 1] += a[i] / 3;
        a[i] = a[i] / 3;
    }
    for (int i = 0; i < 5; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << eat << endl;
    return 0;
}