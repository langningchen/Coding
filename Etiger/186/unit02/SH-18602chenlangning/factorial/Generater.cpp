#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("factorial.in", "w", stdout);
    srand(time(NULL));
    int a = (rand() % 1000 + 1), b = (rand() % 1000 + 1);
    cout << min(a, b) << " " << max(a, b) << endl;
    return 0;
}