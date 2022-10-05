#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, n2;
char a[N];
pair<char, int> a2[N];
void Input()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char t;
        cin >> t;
        t -= 'a';
        a[i] = t;
        if (i > 0 && t == a2[n2 - 1].first)
            a2[n2 - 1].second++;
        else
        {
            a2[n2] = make_pair(t, 1);
            n2++;
        }
    }
}
bool Is0()
{
    return 0;
    // return (n <= 300);
}
void Solve0()
{
    // double Ans = 1.1;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = i; j < n; j++)
    //     {
    //         set<char> Different;
    //         for (int k = i; k <= j; k++)
    //         {
    //             Different.insert(a[k]);
    //         }
    //         if (Different.size() * 1.0 / (j - i + 1) < Ans)
    //         {
    //             Ans = Different.size() * 1.0 / (j - i + 1);
    //         }
    //     }
    // }
    // cout << fixed << setprecision(6) << Ans << endl;
}
bool Is1()
{
    // return 0;
    // return 1;
    return (n <= 300);
}
void Solve1()
{
    double Ans = 1.1;
    for (int i = 0; i < n2; i++)
    {
        for (int j = i; j < n2; j++)
        {
            int Counter = 0;
            set<char> Different;
            for (int k = i; k <= j; k++)
            {
                Counter += a2[k].second;
                Different.insert(a2[k].first);
            }
            if (Different.size() * 1.0 / Counter < Ans)
            {
                Ans = Different.size() * 1.0 / Counter;
            }
        }
    }
    cout << fixed << setprecision(6) << Ans << endl;
}
bool Is2()
{
    return 0;
    for (int i = 0; i < n2; i++)
        if (a2[i].first != 'a' && a2[i].first != 'b')
            return false;
    return true;
}
void Solve2()
{
    for (int i = 0; i < n2; i++)
        if (a2[i].second > n / 2)
        {
            cout << fixed << setprecision(6) << 1.0 / a2[i].second << endl;
            return;
        }
    cout << fixed << setprecision(6) << 2.0 / n << endl;
}
bool Is3()
{
    return 1;
}
void Solve3()
{
    int StartPos, EndPos;
    double StartValue = 1.1, EndValue = 1.1;
    set<char> StartDifferent, EndDifferent;
    for (int i = 0; i < n; i++)
    {
        EndDifferent.insert(a[i]);
        if (EndDifferent.size() * 1.0 / (i + 1) < EndValue)
        {
            EndPos = i;
            EndValue = EndDifferent.size() * 1.0 / (i + 1);
        }
    }
    for (int i = EndPos; i >= 0; i--)
    {
        StartDifferent.insert(a[i]);
        if (StartDifferent.size() * 1.0 / (EndPos - i + 1) < StartValue)
        {
            StartPos = i;
            StartValue = StartDifferent.size() * 1.0 / (EndPos - i + 1);
        }
    }
    // cout << StartPos << " " << EndPos << endl;
    // cout << StartValue << " " << EndValue << endl;
    cout << fixed << setprecision(6) << EndValue << endl;
}
void Solve4()
{
    // queue<pair<char, pair<pair<int, int>, double>>> q;
    // q.push(make_pair(0, make_pair(make_pair(a2[0].second, a2[0].second), 1)));
    // for (int i = 0; i < n2; i++)
    // {
    //     while (!q.empty())
    //     {
    //         pair<char, pair<pair<int, int>, double>> One = q.front();
    //         if (One.first != i)
    //             break;
    //         q.pop();
    //         pair<char, pair<pair<int, int>, double>> Now = One;
    //         Now.first++;
    //         Now.second.first.first++;
    //         Now.second.first.second += a2[Now.first].second;
    //         Now.second.second = Now.second.first.first * 1.0 / Now.second.first.second;
    //         if (Now.second.second >= One.second.second)
    //             q.push(make_pair(Now.first, make_pair(make_pair(1, 1), 1)));
    //         if (Now.second.second <= One.second.second)
    //             q.push(Now);
    //     }
    //     queue<pair<char, pair<pair<int, int>, double>>> t;
    //     while (!q.empty())
    //     {
    //         pair<char, pair<pair<int, int>, double>> One = q.front();
    //         q.pop();
    //         if (t.size() == 0 || t.front().second.second >= One.second.second)
    //         {
    //             while (t.size() > 0 && t.front().second.second > One.second.second)
    //                 t.pop();
    //             t.push(One);
    //         }
    //     }
    //     while (!t.empty())
    //     {
    //         q.push(t.front());
    //         t.pop();
    //     }
    // }
    // cout << q.front() << endl;
}
int main()
{
    freopen("arthas.in", "r", stdin);
    freopen("arthas.out", "w", stdout);
    Input();
    if (Is0())
        Solve0();
    else if (Is1())
        Solve1();
    else if (Is2())
        Solve2();
    else if (Is3())
        Solve3();
    else
        Solve4();
    return 0;
}