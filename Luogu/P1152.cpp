#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, Last;
set<int> s;
int main()
{
    cin >> n;
    cin >> Last;
    for (int i = 1; i < n; i++)
    {
        int Temp;
        cin >> Temp;
        s.insert(abs(Temp - Last));
        Last = Temp;
    }
    if (s.size() == n - 1)
        cout << "Jolly" << endl;
    else
        cout << "Not jolly" << endl;
    return 0;
}