#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int INF = 0x7FFFFFFF;
ll n, t[N];
map<ll, ll> mem;
struct movie
{
    ll s, e, id, ans;
} Movies[N];
bool cmp1(movie &cmp1, movie &cmp2)
{
    if (cmp1.s != cmp2.s)
        return cmp1.s < cmp2.s;
    else
        return cmp1.id < cmp2.id;
}
bool cmp2(movie &cmp1, movie &cmp2)
{
    return cmp1.id < cmp2.id;
}
int main()
{
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        Movies[i].id = i;
    for (int i = 0; i < n; i++)
        cin >> Movies[i].s;
    for (int i = 0; i < n; i++)
        cin >> Movies[i].e;
    Movies[n].s = INF;
    Movies[n].id = n;
    sort(Movies, Movies + n, cmp1);
    for (int i = 0; i < n; i++)
        t[i] = Movies[i].s;
    for (int i = 0; i < n; i++)
    {
        if (mem[Movies[i].e] == 0)
            mem[Movies[i].e] = Movies[upper_bound(t + i + 1, t + n, Movies[i].e) - t].id;
        Movies[i].ans = mem[Movies[i].e] + 1;
    }
    sort(Movies, Movies + n, cmp2);
    for (int i = 0; i < n; i++)
    {
        cout << Movies[i].ans;
        if (i != n - 1)
            cout << " ";
    }
    cout << endl;
    return 0;
}
