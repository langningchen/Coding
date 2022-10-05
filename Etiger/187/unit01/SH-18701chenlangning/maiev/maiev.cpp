#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10005;
const int INF = 0x7FFFFFFF;
int n, SetCount;
set<int> PrimeList, OK, Sets[N];
bool IsPrime[N];
void Init()
{
    IsPrime[0] = false;
    IsPrime[1] = false;
    for (int i = 2; i < N; i++)
        if (IsPrime[i])
        {
            PrimeList.insert(i);
            for (int j = 2; i * j < N; j++)
                IsPrime[i * j] = false;
        }
    for (int i = 2; i < N; i++)
    {
        int x = i;
        int Ans = 0;
        for (set<int>::iterator sit = PrimeList.begin(); sit != PrimeList.end(); sit++)
        {
            if (x % (*sit) == 0)
                Ans++;
            while (x % (*sit) == 0)
                x /= (*sit);
        }
        if (Ans % 2 == 1)
            OK.insert(i);
    }
}
int main()
{
    freopen("maiev.in", "r", stdin);
    freopen("maiev.cpp", "w", stdout);
    cin >> n;
    fill(IsPrime, IsPrime + N, 1);
    Init();
    // for (set<int>::iterator sit = OK.begin(); sit != OK.end(); sit++)
    //     cout << *sit << ", ";
    // cout << endl;
    Sets[0].insert(1);
    SetCount = 1;
    int i = 1;
    while (SetCount < n)
    {
        int BeforeInserted = i, Inserted;
        for (int j = 1; j < N; j++)
        {
            if (OK.find(BeforeInserted + j) != OK.end())
            {
                Sets[0].insert(BeforeInserted + j);
                Inserted = BeforeInserted + j;
                break;
            }
        }
        for (int k = BeforeInserted + 1; k <= Inserted; k++)
        {
            bool flag = false;
            for (int j = 1; j <= SetCount; j++)
            {
                if (OK.find(*Sets[j].end() + k) != OK.end())
                {
                    Sets[j].insert(*Sets[j].end() + k);
                    flag = true;
                }
            }
            if (!flag)
            {
                SetCount++;
                Sets[SetCount].insert(k);
            }
        }
        i = Inserted + 1;
    }
    cout << i - 1 << endl;
    return 0;
}
