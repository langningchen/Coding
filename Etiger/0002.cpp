#include <iostream>
#include <algorithm>

using namespace std;

int a[101];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  *(max_element(a, a + n)) = 100001;
  *(min_element(a, a + n)) = 100001;
  for (int i = 0; i < n; i++) {
    if (a[i] != 100001)
         cout << a[i] << ' ';
  }
  return 0;
}