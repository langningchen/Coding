#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p[605], n, w;
int main() {
	cin >> n >> w;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		p[a]++;
		int Index = 0;
		int Counter = 0;
		while (Index < 600) {
			Counter += p[Index];
			if (Counter >= ceil((i + 1) * 1.0 / w)) break;
			Index++;
		}
		cout << Index << " ";
	}
	return 0;

}
