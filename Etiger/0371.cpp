#include <bits/stdc++.h>
using namespace std;
const int N = 20005;
struct piece
{
    int s, t;
};
bool cmp(const piece &a, const piece &b)
{
    return a.s < b.s || a.s == b.s && a.t < b.t;
}
piece d[N];
int main()
{
    int n, cnt = 0, S = 0, T;
    cin >> T >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        d[i].s = a - b;
        d[i].t = a + b;
    }
    sort(d, d + n, cmp);
    for (int i = 0; i < n && S < T; i++)
    {
        for (int j = i; j < n && d[j].s <= S; j++)
        {
            if (d[j].t > d[i].t)
            {
                i = j;
            }
        }
        if (d[i].s > S)
        {
            break;
        }
        S = d[i].t;
        cnt++;
    }
    if (S < T)
    {
        cout << "Impossible" << endl;
    }
    else
    {
        cout << cnt << endl;
    }
    return 0;
}
