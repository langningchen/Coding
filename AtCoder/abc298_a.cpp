#include <bits/stdc++.h>
using namespace std;
int n;
char c;
bool HasPoor, HasGood;
int main()
{
    cin >> n;
    cin.getline(NULL, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        HasGood = HasGood || (c == 'o');
        HasPoor = HasPoor || (c == 'x');
    }
    cout << (HasGood && !HasPoor ? "Yes" : "No") << endl;
    return 0;
}
