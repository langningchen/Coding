#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
char a[N];
int aLength, kmp[N];
int main()
{
    a[0] = ' ';
    scanf("%s", a + 1);
    while (strcmp(a + 1, "."))
    {
        aLength = strlen(a + 1);
        int j = 0;
        kmp[0] = kmp[1] = 0;
        for (int i = 2; i <= aLength; ++i)
        {
            while (a[i] != a[j + 1] && j != 0)
                j = kmp[j];
            if (a[i] == a[j + 1])
                j++;
            kmp[i] = j;
        }
        if (aLength % (aLength - kmp[aLength]) == 0)
            printf("%d\n", aLength / (aLength - kmp[aLength]));
        else
            printf("1\n");
        scanf("%s", a + 1);
    }
}
