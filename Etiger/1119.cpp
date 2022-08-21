#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
struct Info
{
    int t, id;
} st[N], ed[N];
int n;
bool cmp(const Info &a, const Info &b) 
{
    if (a.t < b.t)
        return 1;
    if (a.t > b.t)
        return 0;
    if (a.id < b.id)
        return 1;
    return 0;
}
int main()
{
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> st[i].t;
        st[i].id = i;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> ed[i].t;
        ed[i].id = i;
    }
    sort(st + 1, st + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
    {
        int l = 1;
        int r = n;
        int ans = n + 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (ed[i].t < st[mid].t)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (ans == n + 1)
            cout << n + 1 << " ";
        else
            cout << st[ans].id << " ";
    }
    return 0;
}