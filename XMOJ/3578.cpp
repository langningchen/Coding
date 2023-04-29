#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
char s[N];
ll k, OneCount;
int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%s%lld", s, &k);
    for (int i = 0; i < strlen(s); i++)
        if (s[i] == '1')
            OneCount++;
        else
            break;
    printf("%c\n", (k <= OneCount) ? '1' : s[OneCount]);
    return 0;
}
