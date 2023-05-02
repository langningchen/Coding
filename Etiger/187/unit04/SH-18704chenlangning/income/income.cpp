#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300005;
ll n, a, x[N], f[N][19];
void Input()
{
    cin >> n >> a;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
}
bool Is1()
{
    bool flag = true;
    for (int i = 0; i < n; i++)
    {
        if (x[i] != 1)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
void Solve1()
{
    if (x[0] == a)
    {
        cout << ((1 + a) * a / 2) << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}
bool Is2()
{
    return 1;
    // return (n <= 1000);
}
void Solve2()
{
    ll Answer = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            ll Sum = 0;
            for (int k = i; k <= j; k++)
            {
                Sum += x[k];
            }
            if (Sum * 1.0 / (j - i + 1) == a)
            {
                Answer++;
            }
            //            cout << i << "\t" << j << "\t" << fixed << setprecision(50) << Sum << "\t" << Answer << endl;
        }
    }
    cout << Answer << endl;
}
void Solve3()
{
    // for (int i = 0; i < n; i++)
    // {
    //     f[i][0] = x[i];
    // }
    // for (int j = 1; (1 << j) < n; j++)
    // {
    //     for (int i = 0; i + (1 << (j - 1)) < n; i += (1 << j))
    //     {
    //         f[i][j] = f[i][j - 1] + f[i + (1 << (j - 1))][j - 1];
    //     }
    // }
    // for (int j = 0; (1 << j) < n; j++)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         cout << f[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = i; j < n; j++)
    //     {
    //         cout << i << " " << j << "  ";
    //         ll l = i;
    //         ll L = j - i + 1;
    //         ll t = 1;
    //         while(L)
    //         {
    //             if (L & 1)
    //             {
    //                 l += t;
    //                 cout << l << " ";
    //             }
    //             t *= 2;
    //             L /= 2;
    //         }
    //         cout << endl;
    //     }
    // }
}
int main()
{
    freopen("income.in", "r", stdin);
    freopen("income.out", "w", stdout);
    Input();
    if (Is1())
    {
        Solve1();
    }
    else if (Is2())
    {
        Solve2();
    }
    else
    {
        Solve3();
    }
    return 0;
}
