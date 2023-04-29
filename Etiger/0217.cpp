#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, n1, n2, wei, ans;
int main()
{
	cin >> n;
	n1 = n;
	n2 = n;
	while (1)
	{
		n1 /= 10;
		wei++;
		if (n1 < 1)
			break;
	}
	for (int loop = 0; loop < wei; loop++)
		if ((floor(n2 / pow(10, loop)) - floor(n2 / pow(10, (loop + 1))) * 10) == 6)
			ans++;
	if (ans == 0)
		cout << "Unhappy";
	for (int loop2 = 0; loop2 < ans; loop2++)
		cout << "6";
	cout << endl;
	return 0;
}
