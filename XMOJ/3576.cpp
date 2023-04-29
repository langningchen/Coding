#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    while (n >= 0)
    {
        if (n % 7 == 0)
        {
            printf("Yes\n");
            return 0;
        }
        n -= 4;
    }
    printf("No\n");
    return 0;
}
