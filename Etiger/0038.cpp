#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
long long n, a[N];
int main()
{
    cin >> n;
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i <= n; i++)
        a[i] = a[i - 1] + a[i - 2];
    cout << a[n] << endl;
    return 0;
}
