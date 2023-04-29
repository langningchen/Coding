#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main()
{
    scanf("%lld", &n);
    for (int i = n; i >= 1; i--)
    {
        if (i % 2 == 1)
            printf("I hate ");
        else
            printf("I love ");
        if (i != 1)
            printf("that ");
    }
    printf("it\n");
    return 0;
}
