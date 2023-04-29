#include <bits/stdc++.h>
using namespace std;
const int N = 15;
char s[N];
bool AC;
int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%s", s);
    AC = true;
    if (s[0] != 'A')
        AC = false;
    int CCounter = 0;
    for (int i = 2; i < strlen(s) - 1; i++)
        if (s[i] == 'C')
            CCounter++;
    if (CCounter != 1)
        AC = false;
    for (int i = 1; i < strlen(s); i++)
        if (s[i] == 'C')
            continue;
        else if (s[i] < 'a' || s[i] > 'z')
            AC = false;
    if (AC)
        printf("AC\n");
    else
        printf("WA\n");
    return 0;
}
