#include <bits/stdc++.h>
using namespace std;
int n, ans_value;
vector<string> ans;
int main()
{
    freopen("longlife.in", "r", stdin);
    freopen("longlife.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string Name, Value;
        cin >> Name >> Value;
        int now = 0;
        for (size_t j = 0; j < Value.size() - 2; j++)
            if (Value[j] == 'T' && Value[j + 1] == 'A' && Value[j + 2] == 'T')
                now++;
        if (now > ans_value)
        {
            ans_value = now;
            ans.clear();
            ans.push_back(Name);
        }
        else if (now == ans_value)
            ans.push_back(Name);
    }
    for (vector<string>::iterator sit = ans.begin(); sit != ans.end(); sit++)
    {
        cout << *sit;
        if (sit != ans.end() - 1)
            cout << " ";
    }
    cout << endl;
    cout << ans_value << endl;
    return 0;
}