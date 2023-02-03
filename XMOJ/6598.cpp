#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n, m, x, y, cnt;
int Head[N];
bool HasWater[N];
struct PIPE
{
    int X, YUp, YDown;
} Pipe[N];
struct EDGE
{
    int To, Depth, Next;
} Edge[N];
int FindIndexByX(int x)
{
    for (int i = 1; i <= n; i++)
        if (Pipe[i].X == x)
            return i;
    return 0;
}
void Do(int To, int From, int Depth)
{
    cnt++;
    Edge[cnt].To = To;
    Edge[cnt].Depth = Depth;
    Edge[cnt].Next = Head[From];
    Head[From] = cnt;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &Pipe[i].X, &Pipe[i].YUp, &Pipe[i].YDown);
        Pipe[i].YDown += Pipe[i].YUp;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int x = 0, d = 0, y = 0;
        scanf("%d%d%d", &x, &y, &d);
        int From = FindIndexByX(x - 1);
        int To = FindIndexByX(x + d);
        int k = 1;
        Do(To, From, y);
        Do(From, To, y);
    }
    scanf("%d%d", &x, &y);
    HasWater[1] = true;
    int Answer = 0;
    while (1)
    {
        while (1)
        {
            bool Flag = false;
            for (int i = 1; i <= n; i++)
                if (HasWater[i])
                {
                    int j = Head[i];
                    while (j)
                    {
                        if ((!HasWater[Edge[j].To]) &&
                            Edge[j].Depth >= Pipe[i].YDown)
                        {
                            HasWater[Edge[j].To] = true;
                            Flag = true;
                        }
                        j = Edge[j].Next;
                    }
                }
            if (!Flag)
                break;
        }
        int MaxDepth = 0;
        for (int i = 1; i <= n; i++)
            if (HasWater[i])
                MaxDepth = max(MaxDepth, Pipe[i].YDown);
        if (HasWater[x] && MaxDepth == y)
            break;
        for (int i = 1; i <= n; i++)
            if (HasWater[i] && Pipe[i].YDown == MaxDepth)
            {
                if (Pipe[i].YDown == Pipe[i].YUp)
                {
                    printf("-1\n");
                    return 0;
                }
                Answer++;
                Pipe[i].YDown--;
            }
    }
    printf("%d\n", Answer);
    return 0;
}
