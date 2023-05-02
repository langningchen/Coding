#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("alchemy.in", "w", stdout);
    srand(time(NULL));
    cout << 100 << endl;
    for (int i = 0; i < 100; i++)
        cout << (rand() % 10000 + 1) << " ";
    cout << endl;
    cout << 99 << endl;
    for (int i = 0; i < 99; i++)
    {
        set<int> s;
        for (int j = 0; j < 100; j++)
        {
            if (rand() % 2 && i != j)
                s.insert(j + 1);
        }
        cout << i + 1 << " " << s.size() << " ";
        for (set<int>::iterator sit = s.begin(); sit != s.end(); sit++)
            cout << *sit << " ";
        cout << endl;
    }
    return 0;
}
