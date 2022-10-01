#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, ans = 1;
int main()
{
    cin >> n;
    for (int i = 2; i <= n; i++)
        ans *= i;
    cout << ans << endl;
    return 0;
}