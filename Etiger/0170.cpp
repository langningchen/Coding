#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
string x[N];
map<string, int> cnt;
set<string> word_list;
int main()
{
    int n, m, k = 0;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string temp;
        cin >> temp;
        word_list.insert(temp);
        k++;
    }
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    int sum = 0, ans = n + 1, ans2 = 0;
    int tail = 0, head = 0;
    while (1)
    {
        while (head < n && sum < k)
        {
            string word = x[head++];
            if (!word_list.count(word))
                continue;
            ++cnt[word];
            if (cnt[word] == 1)
                sum++;
        }
        if (sum < k)
            break;
        ans = min(ans, head - tail);
        string word = x[tail++];
        if (!word_list.count(word))
            continue;
        --cnt[word];
        if (cnt[word] == 0)
            sum--;
        ans2++;
    }
    if (ans == n + 1)
    {
        cout << 0 << endl;
        cout << 0 << endl;
    }
    else
    {
        cout << ans << endl;
        cout << ans2 << endl;
    }
    return 0;
}
