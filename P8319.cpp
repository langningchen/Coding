#include <bits/stdc++.h>
using namespace std;
int Mu, Zi, ans;
int gcd(int x, int y) {
	if (y == 0) return x;
//	cout << x << "/" << y << "=" << x / y << "......" << x % y << endl;
	return gcd(y, x % y);
}
void YueFen() {
	if (Zi == 0 || Mu == 0) return;
	int temp = gcd(Mu, Zi);
	if (temp == 1) return;
	Mu /= temp;
	Zi /= temp;
	ans++;
}
int main() {
	Zi = 0;
	cin >> Mu;
	while (Mu != 1) {
		Zi++;
        ans++;
        if (Zi == Mu) break;
		YueFen();
	cout << Zi << "/" << Mu << endl;
	}
	cout << ans << endl;
	return 0;
}
