#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll n, nX, nY, sX, sY, ansX, ansY;
struct node
{
    ll x, y;
} x[N];
bool cmpx(node &cmp1, node &cmp2)
{
    return cmp1.x > cmp2.x;
}
bool cmpy(node &cmp1, node &cmp2)
{
    return cmp1.y > cmp2.y;
}
int main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> n >> nX >> nY;
    for (ll i = 0; i < n; i++)
        cin >> x[i].x;
    for (ll i = 0; i < n; i++)
        cin >> x[i].y;

    sort(x, x + n, cmpx);
    for (ll i = 0; i < nX; i++)
        sX += x[i].x;
    for (ll i = nX; i < n; i++)
        sY += x[i].y;
    ansX = sX + sY;

    sX = sY = 0;
    sort(x, x + n, cmpy);
    for (ll i = 0; i < nY; i++)
        sY += x[i].y;
    for (ll i = nY; i < n; i++)
        sX += x[i].x;
    ansY = sX + sY;
    // cout << ansX << " " << ansY << endl;
    cout << max(ansX, ansY) << endl;
    return 0;
}