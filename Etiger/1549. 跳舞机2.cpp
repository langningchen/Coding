#include <bits/stdc++.h>
using namespace std;
int n;
double a, g, f;
int main() {
//    freopen("ddr2.in", "r", stdin);
//    freopen("ddr2.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
    	double p;
    	cin >> p;
    	a += p * (3 * E[X(x - 1)] + 3 * g + 1);
    	g = p * (g + 1);
	}
    cout << fixed << setprecision(1) << a << endl;
    return 0;
}

