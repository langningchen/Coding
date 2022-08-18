#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll L, K, x[N], ans1, ans2;
int main()
{
    freopen("auto.in", "r", stdin);
    freopen("auto.out", "w", stdout);
    cin >> L >> K;
    ll l = INF, r = -INF, Sum = 0, AddCounter = 0;
    for (int i = 0; i < L; i++)
    {
        cin >> x[i];
        if (x[i] > 0)
            AddCounter++;
        Sum = max(0ll, Sum + x[i]);
        l = min(l, Sum);
        r = max(r, Sum);
    }
    if (K > AddCounter)
    {
        cout << -2 << endl;
        return 0;
    }
    ll mid, Counter;
    while (r - l > 1)
    {
        mid = (l + r) / 2;
        Counter = 0;
        Sum = 0;
        for (int i = 0; i < L; i++)
        {
            if (Sum + x[i] >= mid)
            {
                Counter++;
                Sum = 0;
            }
            else
            {
                Sum = max(0ll, Sum + x[i]);
            }
        }
        if (Counter > K)
            r = mid;
        else if (Counter < K)
            l = mid;
        else
            break;
    }

    ll Left = l, Right = mid, Middle;
    while (Right - Left > 1)
    {
        Middle = (Left + Right) / 2;
        Counter = 0;
        Sum = 0;
        for (int i = 0; i < L; i++)
        {
            if (Sum + x[i] >= Middle)
            {
                Counter++;
                Sum = 0;
            }
            else
            {
                Sum = max(0ll, Sum + x[i]);
            }
        }
        if (Counter == K)
            Right = Middle;
        else if (Counter < K)
            Left = Middle;
    }
    ans1 = Middle;

    Left = mid;
    Right = r;
    while (Right - Left > 1)
    {
        Middle = (Left + Right) / 2;
        Counter = 0;
        Sum = 0;
        for (int i = 0; i < L; i++)
        {
            if (Sum + x[i] >= Middle)
            {
                Counter++;
                Sum = 0;
            }
            else
            {
                Sum = max(0ll, Sum + x[i]);
            }
        }
        if (Counter == K)
            Left = Middle;
        else if (Counter < K)
            Right = Middle;
    }
    ans2 = Middle - 1;
    if (ans1 > ans2)
        cout << -1 << endl;
    else
        cout << ans1 << " " << ans2 << endl;
    return 0;
}