#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005;
ll n, a[N];
int main()
{
    cin >> n;
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i <= n; i++)
        a[i] = a[i - 1] + a[i - 2];
    for (int i = n; i >= 0; i--)
        cout << a[i] << " ";
    return 0;
}
