#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
int n, m, Top, Position[N], c[N];
int LowBit(int x)
{
    return x & (-x);
}
void Add(int Index, int Value)
{
    while (Index <= n)
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
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++)
    {
        int a = 0;
        scanf("%d", &a);
        if (Position[a])
        {
            m += Top - Position[a] - Sum(Position[a]);
            Add(1, 1);
            Add(Position[a], -1);
        }
        else
            Position[a] = ++Top;
    }
    printf("%d\n", m);
    return 0;
}
