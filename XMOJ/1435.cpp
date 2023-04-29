#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct PEOPLE
{
    int e, s, id, ans;
} People[N];
int T, n, ans, c[N], MaxS;
int LowBit(int x)
{
    return x & (-x);
}
void Add(int Index, int Value)
{
    while (Index <= MaxS)
    {
        c[Index] += Value;
        Index += LowBit(Index);
    }
}
int Sum(int Index)
{
    int ReturnValue = 0;
    while (Index > 0)
    {
        ReturnValue += c[Index];
        Index -= LowBit(Index);
    }
    return ReturnValue;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(c, 0, sizeof(c));
        MaxS = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &People[i].s, &People[i].e);
            People[i].s++;
            People[i].e++;
            MaxS = max(MaxS, People[i].s);
            People[i].id = i;
        }
        sort(People + 1, People + n + 1,
             [](PEOPLE a, PEOPLE b)
             {
                 if (a.e == b.e)
                     return a.s < b.s;
                 return a.e > b.e;
             });
        int SameCounter = 0;
        for (int i = 1; i <= n; i++)
        {
            People[i].ans = Sum(People[i].s);
            if ((People[i].s == People[i - 1].s) &&
                (People[i].e == People[i - 1].e))
            {
                SameCounter++;
                People[i].ans -= SameCounter;
            }
            else
                SameCounter = 0;
            Add(People[i].s, 1);
        }
        sort(People + 1, People + n + 1,
             [](PEOPLE a, PEOPLE b)
             {
                 return a.id < b.id;
             });
        for (int i = 1; i <= n; i++)
            printf("%d\n", People[i].ans);
        printf("\n");
    }
    return 0;
}
