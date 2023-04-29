#include <bits/stdc++.h>
int n, ans, a, b;
int main()
{
    freopen("halloween.in", "r", stdin);
    freopen("halloween.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        ans += a;
    }
    printf("%d", ans);
    return 0;
}
