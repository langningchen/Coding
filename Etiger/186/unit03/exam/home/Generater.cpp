#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("home.in", "w", stdout);
    srand(time(NULL));
    cout << 50 << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << 50 << " " << rand() % 3 + 1 << endl;
        for (int j = 0; j < 50; j++)
        {
            for (int k = 0; k < 50; k++)
                cout << (rand() % 50 ? '.' : 'H');
            cout << endl;
        }
    }
    return 0;
}
