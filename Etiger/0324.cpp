#include <bits/stdc++.h>
using namespace std;
map<string, int> money;
int n, size, times;
int main()
{
    freopen("envelope.in", "r", stdin);
    freopen("envelope.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name;
        char temp;
        cin >> name;
        cin >> size >> temp >> times;
        money[name] -= size * times;
        for (int j = 0; j < times; j++)
        {
            cin >> name;
            money[name] += size;
        }
    }
    cout << money.size() << endl;
    for (map<string, int>::iterator mit = money.begin(); mit != money.end(); mit++)
        cout << mit->first << " " << mit->second << endl;
    return 0;
}
