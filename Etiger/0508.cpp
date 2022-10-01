#include <bits/stdc++.h>
using namespace std;
int n;
set<int> s;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        s.insert(t);
    }
    cout << s.size() << endl;
    for (set<int>::iterator sit = s.begin(); sit != s.end(); sit++)
        cout << *sit << " ";
    cout << endl;
    return 0;
}