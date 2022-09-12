#include <bits/stdc++.h>
using namespace std;
int main()
{
    set<string> film;
    string s;
    int all, ans = 0;
    getline(cin, s);
    s += ' ';
    s.erase(0, s.find(": ") + 2);
    int end = 0;
    while (s.size() > 0)
    {
        end = s.find(" ");
        string temp = s.substr(0, end);
        s.erase(0, end + 1);
        film.insert(temp);
    }
    getline(cin, s);
    s += ' ';
    s.erase(0, s.find(": ") + 2);
    end = 0;
    while (s.size() > 0)
    {
        end = s.find(" ");
        string temp = s.substr(0, end);
        s.erase(0, end + 1);
        if (film.count(temp))
            ans++;
        all++;
    }
    cout << ans << '/' << all << endl;
    return 0;
}
