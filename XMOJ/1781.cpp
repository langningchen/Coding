#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull B = 100000007;
const ull S1 = 10005;
const ull S2 = 1000005;
int main()
{
    ull t;
    scanf("%llu", &t);
    while (t--)
    {
        char s1[S1], s2[S2];
        scanf("%s%s", s1, s2);
        ull Count = 0;
        ull s1Length = strlen(s1);
        ull s2Length = strlen(s2);
        ull t = 1;
        for (ull i = 0; i < s1Length; i++)
            t *= B;
        ull s1h = 0, s2h = 0;
        for (ull i = 0; i < s1Length; i++)
            s1h = s1h * B + s1[i];
        for (ull i = 0; i < s1Length; i++)
            s2h = s2h * B + s2[i];
        for (ull i = 0; i + s1Length <= s2Length; i++)
        {
            if (s1h == s2h)
                Count++;
            if (i + s1Length < s2Length)
                s2h = s2h * B + s2[i + s1Length] - s2[i] * t;
        }
        printf("%llu\n", Count);
    }
    return 0;
}
