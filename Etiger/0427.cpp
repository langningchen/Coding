#include <bits/stdc++.h>
using namespace std;
int a;
double l = -5, r = 5, m, ans;
const double wc = 0.000001;
double jcf(double x, int n)
{
	double xnew = 1;
	for (int i = 0; i < n; i++)
		xnew *= x;
	return xnew;
}
double f(double m)
{
	return jcf(m, 3) + jcf(m, 2) + m;
}
int main()
{
	cin >> a;
	while (r - l > wc)
	{
		m = (l + r) / 2;
		ans = f(m);
		if (ans < a)
			l = m;
		else if (ans > a)
			r = m;
	}
	cout << fixed << setprecision(3) << m << endl;
	return 0;
}
