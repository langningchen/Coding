#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A1, A2, A3;
int main()
{
#ifndef __LOCAL__
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &A1, &A2, &A3);
    printf("%lld\n", max(max(abs(A1 - A2), abs(A2 - A3)), abs(A3 - A1)));
    return 0;
}
