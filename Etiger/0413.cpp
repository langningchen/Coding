#include <bits/stdc++.h>
#include <set>
using namespace std;
int main() {
    int n, ans = 0, a[2000], b[2000];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(b, b + n);
//    for (int i = 0; i < n; i++) {
//        cout << a[i] << " ";
//    }
//    cout << endl;
//    for (int i = 0; i < n; i++) {
//        cout << b[i] << " ";
//    }
//    cout << endl;
    sort(b, b + n);
    int m = n;
    for (int i = 0; i < m; i++) {
        if (b[0] > a[n - 1]) {
//            cout << i << " " << b[0] << " " << a[n - 1] << "!!!" << endl;
            ans -= 200;
            n--;
            for (int k = 0; k < n; k++) {
                b[k] = b[k + 1];
            }
        }
        else {
            int l = 0, r = n - 1;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (a[mid] > b[0]) {
                    r = mid;
                }
                if (a[mid] < b[0]) {
                    l = mid;
                }
            }
            if (a[r] != b[0]) {
                ans += 200;
            }
//            cout << i << " " << l << " " << r << " " << a[r] << " " << b[0] << " " << ans << endl;
            n--;
            for (int k = r; k < n; k++) {
                a[k] = a[k + 1];
            }
            for (int k = i; k < n; k++) {
                b[k] = b[k + 1];
            }
        }
        
        
        
//        cout << endl;
//        for (int i = 0; i < n; i++) {
//            cout << a[i] << " ";
//        }
//        cout << endl;
//        for (int i = 0; i < n; i++) {
//            cout << b[i] << " ";
//        }
//        cout << endl;
//        cout << endl;
    
    
    
    }
    cout << ans << endl;
    return 0;
}
