#include <bits/stdc++.h>
using namespace std;
const int N = 205;
char s[N], t[N];
int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%s%s", s, t);
    reverse(s, s + strlen(s));
    reverse(t, t + strlen(t));
    strcpy(s + strlen(s), s);
    char *FoundedPos = strstr(s, t);
    if (FoundedPos == NULL)
        puts("-1");
    else
        printf("%d\n", (int)(FoundedPos - s));
    return 0;
}
