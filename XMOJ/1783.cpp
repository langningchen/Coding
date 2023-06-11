#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull N = 400005;
const ull P = 256;
char s[N];
ull h[N], p[N];
int main()
{
    while (scanf("%s", s + 1) != EOF)
    {
        p[0] = 1;
        h[0] = 0;
        ull sLength = strlen(s + 1);
        for (ull i = 1; i <= sLength; ++i)
        {
            p[i] = p[i - 1] * P;
            h[i] = h[i - 1] * P + s[i];
        }
        for (ull i = 1; i <= sLength; ++i)
            if (h[i] == h[sLength] - h[sLength - i] * p[i])
                printf("%d ", i);
        printf("\n");
    }
    return 0;
}
