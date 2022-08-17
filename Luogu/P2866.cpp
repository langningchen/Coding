#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 80005;
int n, st[N], top, h;
ll ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> h;
        while (top > 0 && h >= st[top])
            top--;
        ans += top;
        top++;
        st[top] = h;
    }
    cout << ans << endl;
    return 0;
}