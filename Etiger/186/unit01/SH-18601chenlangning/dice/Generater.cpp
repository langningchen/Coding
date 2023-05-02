#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("dice.in", "w", stdout);
    srand(time(NULL));
    cout << 100000 << endl;
    for (int i = 0; i < 100000; i++)
        cout << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << " "
             << (rand() % 10 + 1) << endl;
    return 0;
}