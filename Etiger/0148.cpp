#include <bits/stdc++.h>
using namespace std;
const int N = 105;
double girls[N], boys[N];
int main()
{
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	int n, nGirls = 0, nBoys = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string s;
		double h;
		cin >> s >> h;
		if (s[0] == 'm')
			boys[nBoys++] = h;
		else
			girls[nGirls++] = h;
	}
	sort(boys, boys + nBoys);
	sort(girls, girls + nGirls);
	for (int i = 0; i < nBoys; i++)
		cout << fixed << setprecision(2) << boys[i] << " ";
	for (int i = nGirls - 1; i >= 0; i--)
		cout << fixed << setprecision(2) << girls[i] << " ";
	return 0;
}
