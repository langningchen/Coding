#include <bits/stdc++.h>
using namespace std;
struct TRIP {
	int Type;
	int Price;
	int Time;
    bool operator < (const TRIP cmp) const {
    	return Time < cmp.Time;
	}
};
struct PAPER {
	int Price;
	int Time;
    bool operator < (const PAPER cmp) const {
    	return Time < cmp.Time;
	}
};
set<TRIP> Trips;
set<PAPER> Papers;
int n, ans;
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		Trips.insert((TRIP){a, b, c});
	}
	for (set<TRIP>::iterator sit = Trips.begin(); sit != Trips.end(); sit++) {
		bool flag = false;
		if (sit->Type == 0) {
			Papers.insert((PAPER){sit->Price, sit->Time + 45});
		}
		else {
			for (set<PAPER>::iterator mit = Papers.begin(); mit != Papers.end(); ) {
				if (sit->Time > mit->Time) {
					mit = Papers.erase(mit);
				}
				else {
					if (sit->Price <= mit->Price) {
						Papers.erase(mit);
						flag = true;
						break;
					}
					mit++;
				}
			}
		}
		if (!flag) {
			ans += sit->Price;
		}
	}
	cout << ans << endl;
	return 0;
}

