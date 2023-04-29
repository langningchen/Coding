#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
struct POSITION
{
    int x, y;
} Position[N];
int n, MaxX, c[N], AnswerCounter[N];
int LowBit(int x)
{
    return x & (-x);
}
void Add(int Index, int Value)
{
    while (Index <= MaxX)
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
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &Position[i].x, &Position[i].y);
        Position[i].x++;
        Position[i].y++;
        MaxX = max(MaxX, Position[i].x);
    }
    sort(Position + 1, Position + n + 1,
         [](POSITION a, POSITION b)
         {
             if (a.y == b.y)
                 return a.x < b.x;
             return a.y < b.y;
         });
    for (int i = 1; i <= n; i++)
    {
        int Counter = 0;
        AnswerCounter[Sum(Position[i].x)]++;
        Add(Position[i].x, 1);
    }
    for (int i = 0; i < n; i++)
        printf("%d\n", AnswerCounter[i]);
    return 0;
}
