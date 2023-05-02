#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 2005;
const int M = 100005;
const int INF = 0x7FFFFFFF;
int n, m, a[N][2];
bool IsPrime[M * 2];
void Input()
{
    fill(IsPrime, IsPrime + M * 2, true);
    IsPrime[0] = IsPrime[1] = false;
    for (int i = 2; i < M * 2; i++)
        if (IsPrime[i])
            for (int j = 2; i * j < M * 2; j++)
                IsPrime[i * j] = false;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i][0] >> a[i][1];
}
int GetLength(int x, int y)
{
    return (abs(a[x][0] - a[y][0]) + abs(a[x][1] - a[y][1]));
}
bool Is0()
{
    return false;
    return (n == 3);
}
void Solve0()
{
    int d1 = GetLength(0, 1);
    int d2 = GetLength(1, 2);
    int d3 = GetLength(2, 0);
    if (d1 > d2)
        swap(d1, d2);
    if (d2 > d3)
        swap(d2, d3);
    if (d1 > d2)
        swap(d1, d2);
    if (IsPrime[d2])
        cout << 1 << endl;
    else
        cout << 0 << endl;
}
bool Is1()
{
    return (n <= 550);
}
void Solve1()
{
    ull Answer = 0;
    for (int x1 = 0; x1 < n; x1++)
    {
        for (int x2 = x1 + 1; x2 < n; x2++)
        {
            for (int x3 = x2 + 1; x3 < n; x3++)
            {
                int d1 = GetLength(x1, x2);
                int d2 = GetLength(x2, x3);
                int d3 = GetLength(x3, x1);
                if (d1 > d2)
                    swap(d1, d2);
                if (d2 > d3)
                    swap(d2, d3);
                if (d1 > d2)
                    swap(d1, d2);
                if (IsPrime[d2])
                    Answer++;
            }
        }
    }
    cout << Answer << endl;
}
void Solve2()
{
    ull Answer = 0;
    vector<int> LengthList;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            LengthList.push_back(GetLength(i, j));
    sort(LengthList.begin(), LengthList.end());
    int Counter = 0;
    int LenthList_Size = LengthList.size();
    for (vector<int>::iterator sit = LengthList.begin(); sit != LengthList.end(); sit++)
    {
        if (IsPrime[*sit])
            Answer += Counter * (LenthList_Size - Counter - 1);
        Counter++;
    }
    cout << Answer << endl;
}
int main()
{
    freopen("mama.in", "r", stdin);
    freopen("mama.out", "w", stdout);
    Input();
    if (Is0())
        Solve0();
    else if (Is1())
        Solve1();
    else
        Solve2();
    return 0;
}