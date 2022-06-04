#include <bits/stdc++.h>
using namespace std;
int main() {
    map<string, int> word;
    string s;
    while(cin >> s)
        word[s]++;
    int ans = 0;
    for (map<string, int>::iterator mit = word.begin(); mit != word.end(); mit++)
        if (mit->second >= ans)
            ans = mit->second;
    for (map<string, int>::iterator mit = word.begin(); mit != word.end(); mit++)
        if (mit->second == ans) {
            cout << mit->first << endl;
            break;
        }
    return 0;
}
