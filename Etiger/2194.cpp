#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, k, zi, mu, g;
struct Course
{
    int a, b, v;
} d[N];
bool cmp(Course a, Course b)
{
    return a.v < b.v;
}
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int cal(double x)
{
    for (int i = 1; i <= n; i++)
        d[i].v = 1.0 * d[i].b * (d[i].a - x);
    sort(d + 1, d + 1 + n, cmp);
    double sum = 0.0;
    for (int i = 1; i <= n - k; i++)
        sum += d[i].v;
    return (sum >= 0.0);
}
void get(double x)
{
    for (int i = 1; i <= n; i++)
        d[i].v = 1.0 * d[i].b * (d[i].a - x);
    sort(d + 1, d + 1 + n, cmp);
    for (int i = 1; i <= n - k; i++)
    {
        zi += d[i].a * d[i].b;
        mu += d[i].b;
    }
    g = gcd(mu, zi);
    cout << zi / g;
    if (mu != g)
        cout << "/" << mu / g;
    cout << endl;
}
int main()
{
    // freopen("curriculum.in", "r", stdin);
    // freopen("curriculum.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> d[i].a >> d[i].b;
    double l = 0.0, r = 1e13, mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (cal(mid) == 1)
            l = mid + 0.0001;
        else
            r = mid - 0.0001;
    }
    get(mid);
    return 0;
}