#include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= 'a' && s[i] <= 'z')
      s[i] = s[i] - 'a' + 'A';
       else if (s[i] >= 'A' && s[i] <= 'Z')
      s[i] = s[i] - 'A' + 'a';
  }
  cout << s;
  return 0;
}
