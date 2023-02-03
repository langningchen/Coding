#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll T, n, a[2 * N], aCopy[N], Temp[N], Counter;
void MergeSort(ll *ArrayToSort, ll LeftBound, ll RightBound)
{
    if (LeftBound == RightBound)
        return;
    ll MiddleBound = (LeftBound + RightBound) / 2;
    MergeSort(ArrayToSort, LeftBound, MiddleBound);
    MergeSort(ArrayToSort, MiddleBound + 1, RightBound);
    ll LeftArrayPointer = LeftBound;
    ll RightArrayPointer = MiddleBound + 1;
    ll TempSize = 0;
    while (LeftArrayPointer <= MiddleBound && RightArrayPointer <= RightBound)
        if (ArrayToSort[LeftArrayPointer] <= ArrayToSort[RightArrayPointer])
            Temp[TempSize++] = ArrayToSort[LeftArrayPointer++];
        else
        {
            Temp[TempSize++] = ArrayToSort[RightArrayPointer++];
            Counter += MiddleBound - LeftArrayPointer + 1;
        }
    while (LeftArrayPointer <= MiddleBound)
        Temp[TempSize++] = ArrayToSort[LeftArrayPointer++];
    while (RightArrayPointer <= RightBound)
        Temp[TempSize++] = ArrayToSort[RightArrayPointer++];
    for (ll i = LeftBound; i <= RightBound; i++)
        ArrayToSort[i] = Temp[i - LeftBound];
}
int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        for (ll i = 0; i < n; i++)
        {
            scanf("%lld", &a[i]);
            a[i + n] = a[i];
            aCopy[i] = a[i];
        }
        Counter = 0;
        MergeSort(aCopy, 0, n - 1);
        ll ans = Counter;
        for (ll i = 1; i < n; i++)
        {
            /*
             * n = 10
             *
             *       a[] = 1 3 6 9 0 8 5 7 4 2   1 3 6 9 0 8 5 7 4 2
             * i = 1:      -------------------
             *
             *       a[] = 1 3 6 9 0 8 5 7 4 2   1 3 6 9 0 8 5 7 4 2
             * i = 2:        ---------------------
             *       =     ------------------- (i = 1)
             *         -   --
             *         +                      ----
             *       =     --------i=1--------
             *         -   1 ------ <1 -------
             *         +     ------ >1 -------   1
             *
             *       a[] = 1 3 6 9 0 8 5 7 4 2   1 3 6 9 0 8 5 7 4 2
             * i = 3:          ---------------------
             *      =        ---------i=2---------
             *         -     3 ------- <3 --------
             *         +       ------- >3 -------- 3
             *
             *       a[] = 1 3 6 9 0 8 5 7 4 2   1 3 6 9 0 8 5 7 4 2
             * i = k:      ...       ---------------------
             *      =      ...     --------i=k-1--------
             *         -   ...  a[k-1] ---- <a[k-1] ----
             *         +   ...         ---- >a[k-1] ---- a[k-1]
             *
             * Answer(k) = Answer(k - 1) -
             *             Count(a[k] ~ a[n - 1] where value<a[k-1]) +
             *             Count(a[k] ~ a[n - 1] where value>a[k-1])
             *
             * Count(a[k] ~ a[n - 1] where value<a[k-1]) = a[k]
             * Count(a[k] ~ a[n - 1] where value>a[k-1]) = n - 1 - a[k]
             * Answer(k) = Answer(k - 1) - a[k - 1] + n - 1 - a[k - 1]
             *           = Answer(k - 1) + n - 1 - 2 * a[k - 1]
             */
            Counter += n - 1 - 2 * a[i - 1];
            ans = min(ans, Counter);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
