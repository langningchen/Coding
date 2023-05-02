#include <cstdio>
const int N = 100005;
int Root, Total, Father[N], Child[N][2], Value[N], Count[N], Size[N];
void PushUp(int x)
{
    Size[x] = Size[Child[x][0]] + Size[Child[x][1]] + Count[x];
}
bool Get(int x)
{
    return x == Child[Father[x]][1];
}
void Clear(int x)
{
    Child[x][0] = Child[x][1] = Father[x] = Value[x] = Size[x] = Count[x] = 0;
}
void Rotate(int x)
{
    int y = Father[x];
    int z = Father[y];
    int chk = Get(x);
    Child[y][chk] = Child[x][chk ^ 1];
    if (Child[x][chk ^ 1])
        Father[Child[x][chk ^ 1]] = y;
    Child[x][chk ^ 1] = y;
    Father[y] = x;
    Father[x] = z;
    if (z)
        Child[z][y == Child[z][1]] = x;
    PushUp(y);
    PushUp(x);
}
void Splay(int x)
{
    int f = Father[x];
    while (f != 0)
    {
        if (Father[f])
            Rotate(Get(x) == Get(f) ? f : x);
        Rotate(x);
        f = Father[x];
    }
    Root = x;
}
void Insert(int x)
{
    if (!Root)
    {
        Value[++Total] = x;
        Count[Total]++;
        Root = Total;
        PushUp(Root);
        return;
    }
    int Current = Root;
    int f = 0;
    while (1)
    {
        if (Value[Current] == x)
        {
            Count[Current]++;
            PushUp(Current);
            PushUp(f);
            Splay(Current);
            break;
        }
        f = Current;
        Current = Child[Current][Value[Current] < x];
        if (!Current)
        {
            Value[++Total] = x;
            Count[Total]++;
            Father[Total] = f;
            Child[f][Value[f] < x] = Total;
            PushUp(Total);
            PushUp(f);
            Splay(Total);
            break;
        }
    }
}
int rk(int x)
{
    int Answer = 0;
    int Current = Root;
    while (1)
    {
        if (x < Value[Current])
        {
            Current = Child[Current][0];
        }
        else
        {
            Answer += Size[Child[Current][0]];
            if (x == Value[Current])
            {
                Splay(Current);
                return Answer + 1;
            }
            Answer += Count[Current];
            Current = Child[Current][1];
        }
    }
}
int kth(int x)
{
    int Current = Root;
    while (1)
    {
        if (Child[Current][0] && x <= Size[Child[Current][0]])
        {
            Current = Child[Current][0];
        }
        else
        {
            x -= Count[Current] + Size[Child[Current][0]];
            if (x <= 0)
            {
                Splay(Current);
                return Value[Current];
            }
            Current = Child[Current][1];
        }
    }
}
int PreNode()
{
    int Current = Child[Root][0];
    if (!Current)
        return Current;
    while (Child[Current][1])
        Current = Child[Current][1];
    Splay(Current);
    return Current;
}
int NextNode()
{
    int Current = Child[Root][1];
    if (!Current)
        return Current;
    while (Child[Current][0])
        Current = Child[Current][0];
    Splay(Current);
    return Current;
}
void Delete(int x)
{
    rk(x);
    if (Count[Root] > 1)
    {
        Count[Root]--;
        PushUp(Root);
        return;
    }
    if (!Child[Root][0] && !Child[Root][1])
    {
        Clear(Root);
        Root = 0;
        return;
    }
    if (!Child[Root][0])
    {
        int Current = Root;
        Root = Child[Root][1];
        Father[Root] = 0;
        Clear(Current);
        return;
    }
    if (!Child[Root][1])
    {
        int Current = Root;
        Root = Child[Root][0];
        Father[Root] = 0;
        Clear(Current);
        return;
    }
    int Current = Root;
    int Temp = PreNode();
    Father[Child[Current][1]] = Temp;
    Child[Temp][1] = Child[Current][1];
    Clear(Current);
    PushUp(Root);
}
int n;
int main()
{
    scanf("%d", &n);
    while (n-- > 0)
    {
        int Operation, x;
        scanf("%d%d", &Operation, &x);
        if (Operation == 1)
            Insert(x);
        else if (Operation == 2)
            Delete(x);
        else if (Operation == 3)
            printf("%d\n", rk(x));
        else if (Operation == 4)
            printf("%d\n", kth(x));
        else if (Operation == 5)
        {
            Insert(x);
            printf("%d\n", Value[PreNode()]);
            Delete(x);
        }
        else
        {
            Insert(x);
            printf("%d\n", Value[NextNode()]);
            Delete(x);
        }
    }
    return 0;
}
