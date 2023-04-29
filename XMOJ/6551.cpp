#include <bits/stdc++.h>
using namespace std;
int n, k = 1, tmp;
int pri[200] = {0, 2};
long long ans[1010], Answer;
int main()
{
    scanf("%d", &n);
    if (n == 1)
    {
        printf("1");
        return 0;
    }
    for (int i = 3; i <= n; i += 2)
    {
        pri[++k] = i;
        for (int j = 2; j < k; ++j)
        {
            if (i % pri[j] == 0)
            {
                k--;
                break;
            }
        }
    }
    ans[0] = 1;
    for (int i = 1; i <= k; ++i)
    {
        for (int j = n; j >= pri[i]; --j)
        {
            tmp = pri[i];
            while (tmp <= j)
            {
                ans[j] += ans[j - tmp];
                tmp *= pri[i];
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        Answer += ans[i];
    printf("%lld", Answer + 1);
    return 0;
}
