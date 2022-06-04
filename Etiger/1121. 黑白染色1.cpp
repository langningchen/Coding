#include <iostream>
#include <string>
using namespace std;
unsigned int m, ai, bi, x[200001], i = 1;
string str;
int main() {
    cin >> str;
    for (i = 1; i <= str.length(); i++)
        if (str.data()[i - 1] == 'W')
            x[i] = x[i - 1];
        else if (str.data()[i - 1] == 'B')
            x[i] = x[i - 1] + 1;
    cin >> m;
    for (i = 0; i < m; i++) {
        cin >> ai >> bi;
        cout << x[bi] - x[ai - 1] << ' ';
    }
    return 0;
}
