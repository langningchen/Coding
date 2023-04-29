#include <bits/stdc++.h>
using namespace std;
double a, b, c, d;
int main()
{
	cin >> a >> b >> c >> d;
	cout << fixed << setprecision(1) << fabs(c - a) + fabs(d - b) << endl;
	return 0;
}
