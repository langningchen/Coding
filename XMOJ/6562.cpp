#include <bits/stdc++.h>
using namespace std;
const int N = 20005;
const int INF = 200000000;
struct NUMBER
{
    int x;
    friend bool operator<(NUMBER a, NUMBER b)
    {
        return a.x > b.x;
    }
} f[N];
int n, m, a[N], d[N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        f[i].x = 0;
    }
    int k = 0;
    f[0].x = INF;
    for (int i = n; i >= 1; i--)
    {
        if (a[i] < f[k].x)
        {
            f[++k].x = a[i];
            d[i] = k;
        }
        else
        {
            NUMBER tt;
            tt.x = a[i];
            int t = lower_bound(f, f + k + 1, tt) - f;
            f[t] = tt;
            d[i] = t;
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int l;
        scanf("%d", &l);
        if (f[l].x == 0)
        {
            printf("Impossible\n");
        }
        else
        {
            int Answer = -1;
            for (int j = 1; j <= n; j++)
                if (a[j] > Answer && d[j] >= l && l >= 1)
                {
                    printf("%d ", a[j]);
                    Answer = a[j];
                    l--;
                }
            printf("\n");
        }
    }
    return 0;
}