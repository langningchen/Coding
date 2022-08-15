#include <bits/stdc++.h>
using namespace std;
int n;
double BikeTime, WalkTime;
int main()
{
    cin >> n;
    BikeTime = 50 + n / 3.0;
    WalkTime = n / 1.2;
    if (BikeTime < WalkTime)
        cout << "Bike" << endl;
    else if (BikeTime > WalkTime)
        cout << "Walk" << endl;
    else
        cout << "All" << endl;
    return 0;
}