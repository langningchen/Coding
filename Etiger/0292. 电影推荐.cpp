#include <bits/stdc++.h>
using namespace std;
int main() {
    set<string> film;
    string s;
    int all, ans = 0;
    getline(cin, s);
    s += ' ';
    s.erase(0, s.find(": ") + 2);
    int end = 0;
    while(s.size() > 0) {
        end = s.find(" ");
        string temp = s.substr(0, end);
        s.erase(0, end + 1);
//        cout << s << '#' << temp << '#' << s.size() << endl;
//        getchar();
        film.insert(temp);
    }

//    for (set<string>::iterator it = film.begin(); it != film.end(); it++) {
//        cout << *it << endl;
//    }

    getline(cin, s);
    s += ' ';
    s.erase(0, s.find(": ") + 2);
    end = 0;
    while(s.size() > 0) {
        end = s.find(" ");
        string temp = s.substr(0, end);
        s.erase(0, end + 1);
//        cout << s << '#' << temp << '#' << s.size() << endl;
//        getchar();
        if (film.count(temp))
            ans++;
        all++;
    }

//        if (s[0] >= 'A' && s[0] <= 'Z')
//            break;
//        film.insert(s);
//        all1++;
//    }
//    while(c = getchar(), c != ':'){};
//    while(cin >> s) {
//        if (film.count(s))
//            ans++;
//        all2++;
//    }
    cout << ans << '/' << all<< endl;
    return 0;
}
