#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("blast.in", "w", stdout);
    srand(time(NULL));
    cout << 10000 << endl;
    for (int i = 0; i < 10000; i++)
        cout << (rand() % 100000000) << " ";
    cout << endl;
    // freopen("blast.in", "r", stdin);
    // int n;
    // cin >> n;
    // multiset<long long> t;
    // for (int i = 0; i < n; i++)
    // {
    //     long long te;
    //     cin >> te;
    //     t.insert(te);
    // }
    // for (set<long long>::iterator sit = t.begin(); sit != t.end();)
    // {
    //     int a = *sit;
    //     sit++;
    //     int b = *sit;
    //     if (b - a == 1 || b == a)
    //     {
    //         cout << true << endl;
    //         break;
    //     }
    // }
    return 0;
}