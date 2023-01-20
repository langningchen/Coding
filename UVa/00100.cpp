#include <bits/stdc++.h>
using namespace std;
int GetCycle(int n)
{
    int ans = 1;
    while (n != 1)
    {
        ans++;
        if (n % 2)
            n = 3 * n + 1;
        else
            n /= 2;
    }
    return ans;
}
int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        cout << a << " " << b << " ";
        if (a > b)
            swap(a, b);
        int ans = 0;
        for (int i = a; i <= b; i++)
            ans = max(ans, GetCycle(i));
        cout << ans << endl;
    }
    return 0;
}
