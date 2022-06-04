#include <iostream>
using namespace std;
int main() {
    int n, temp;
    long long sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        sum += temp;
        cout << sum << ' ';
    }
    return 0;
}
