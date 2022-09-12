#include <bits/stdc++.h>
using namespace std;
map<string, int> d;
map<string, int>::iterator mit;
int n;
int main()
{
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name;
        int score;
        cin >> name >> score;
        if (d.count(name) == 0 || d[name] < score)
            d[name] = score;
    }
    cout << d.size() << endl;
    for (mit = d.begin(); mit != d.end(); mit++)
        cout << mit->first << " " << mit->second << endl;
    return 0;
}
