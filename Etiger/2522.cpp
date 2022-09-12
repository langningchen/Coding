#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
const int Y = 10005;
struct Point
{
    int x, y, id;
} p[N];
int n, bit[Y], ans[N];
bool cmpX(const Point &a, const Point &b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}
int LSB(int i)
{
    return i & (-i);
}
void add(int i)
{
    for (; i <= Y; i += LSB(i))
        bit[i]++;
}
int psq(int i)
{
    int sum = 0;
    for (; i; i -= LSB(i))
        sum += bit[i];
    return sum;
}
int main()
{
    freopen("lowerleft.in", "r", stdin);
    freopen("lowerleft.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }
    sort(p + 1, p + 1 + n, cmpX);
    for (int i = 1; i <= n; i++)
    {
        ans[p[i].id] = psq(p[i].y);
        add(p[i].y);
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    return 0;
}
