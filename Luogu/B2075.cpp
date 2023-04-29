#include <bits/stdc++.h>
using namespace std;
int a, b, ans = 1;
int main()
{
    cin >> a >> b;
    for (int i = 0; i < b; i++)
        ans = ans * a % 1000;
    cout << (ans < 100 ? "0" : "") << (ans < 10 ? "0" : "") << ans << endl;
    return 0;
}