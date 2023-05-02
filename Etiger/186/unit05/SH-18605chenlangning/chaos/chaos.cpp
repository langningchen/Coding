#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll n, counter, Start, End;
short c[N];
set<int> history;
double Min = 1;
int main()
{
    freopen("chaos.in", "r", stdin);
    freopen("chaos.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char t;
        cin >> t;
        c[i] = t - 'a';
    }
    for (int i = 0; i < n; i++)
    {
        if (history.count(c[i]) == 0)
        {
            counter++;
            history.insert(c[i]);
        }
        if (counter * 1.0 / (i + 1) <= Min)
        {
            Min = counter * 1.0 / (i + 1);
            End = i;
        }
    }
    Min = 1;
    counter = 0;
    history.clear();
    for (int i = End; i >= 0; i--)
    {
        if (history.count(c[i]) == 0)
        {
            counter++;
            history.insert(c[i]);
        }
        if (counter * 1.0 / (End - i + 1) <= Min)
        {
            Min = counter * 1.0 / (End - i + 1);
            Start = i;
        }
    }
    for (int i = Start; i <= End; i++)
        cout << (char)(c[i] + 'a');
    cout << endl;
    return 0;
}