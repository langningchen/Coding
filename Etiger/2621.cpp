#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int T, n1, n2, c1, c2, m, d[N];
struct Cover
{
    int date, num;
};
int F(int m)
{
    int cost = 0;
    deque<Cover> q1, q2;
    for (int i = 1; i <= T; i++)
    {
        int demand = d[i];
        int cnt = min(demand, m);
        demand -= cnt;
        m -= cnt;
        if (i - n2 > 0)
            q2.push_back((Cover){i - n2, d[i - n2]});
        while (!q2.empty())
        {
            if (q2.front().date + n1 > i)
                break;
            q1.push_back(q2.front());
            q2.pop_front();
        }
        while (!q1.empty() && demand)
        {
            cnt = min(demand, q1.front().num);
            cost += cnt * c1;
            demand -= cnt;
            q1.front().num -= cnt;
            if (!q1.front().num)
                q1.pop_front();
        }
        while (!q2.empty() && demand)
        {
            cnt = min(demand, q2.back().num);
            cost += cnt * c2;
            demand -= cnt;
            q2.back().num -= cnt;
            if (!q2.back().num)
                q2.pop_back();
        }
        if (demand)
            return -1;
    }
    return cost;
}
int main()
{
    freopen("tablecloth.in", "r", stdin);
    freopen("tablecloth.out", "w", stdout);
    cin >> T >> n1 >> n2 >> c1 >> c2 >> m;
    for (int i = 1; i <= T; i++)
        cin >> d[i];
    if (c1 > c2)
    {
        swap(n1, n2);
        swap(c1, c2);
    }
    if (n1 <= n2)
    {
        c2 = c1;
        n2 = n1;
    }
    cout << F(m) << endl;
    return 0;
}