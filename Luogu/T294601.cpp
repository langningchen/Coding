/*
# 提高 T4 - 集合

## 题目描述

给定 $n$ 个集合 $S_i$，其中第 $i$ 个集合包含了 $[l_i,r_i]$ 内的所有整数。

进行 $m$ 次询问，每次给定 $[l,r]$，你需要求出：

$$\left|\bigcup_{S_i\subseteq [l,r]}S_i\right|$$

即所有被 $[l,r]$ 包含的集合的并集大小。

为了减少输出量，你只需要输出所有答案的异或和。

## 输入格式

第一行，两个数，依次表示 $n,m$。

接下来 $n$ 行，每行两个数，第 $i$ 行的数依次表示 $l_i,r_i$。

接下来 $m$ 行，每行两个数，依次表示一次询问中的 $l,r$。

## 输出格式

共一行，一个数，表示答案。

## 样例 #1

### 样例输入 #1

```
3 4
1 2
2 3
1 4
1 3
2 3
2 4
1 5
```

### 样例输出 #1

```
7
```

## 提示

对于 $100\%$ 的数据，$1\le n\le 2\times 10^5,1\le m\le 10^6,1\le l_i\le r_i\le 10^9,1\le l\le r\le 10^9$。

$\operatorname{Subtask} 1(5\%):n,m,l_i,r_i,l,r\le 100$。

$\operatorname{Subtask} 2(10\%):n,m\le 10^4$。

$\operatorname{Subtask} 3(20\%):n\le 10^4$。

$\operatorname{Subtask} 4(15\%):n\le 10^5,m\le 2\times 10^5,\forall i\in [1,n),l_i\le l_{i+1},r_i\le r_{i+1}$。

$\operatorname{Subtask} 5(20\%):n\le 10^5,m\le 2\times 10^5$。

$\operatorname{Subtask} 6(30\%):$ 无特殊限制。

#### 样例说明 1

三个集合分别为 $\{1,2\},\{2,3\},\{1,2,3,4\}$。

被 $[1,3]$ 包含的集合为 $\{1,2\},\{2,3\}$，并集为 $\{1,2,3\}$。

被 $[2,3]$ 包含的集合为 $\{2,3\}$，并集为 $\{2,3\}$。

被 $[2,4]$ 包含的集合为 $\{2,3\}$，并集为 $\{2,3\}$。

被 $[1,5]$ 包含的集合为 $\{1,2\},\{2,3\},\{1,2,3,4\}$，并集为 $\{1,2,3,4\}$。

因此四次询问答案依次为 $3,2,2,4$，它们的异或和为 $7$。
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, l[N], r[N], ans;
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> l[i] >> r[i];
        if (r[i] < l[i])
            swap(l[i], r[i]);
    }
    for (int i = 0; i < m; i++)
    {
        int ll, rr;
        cin >> ll >> rr;
        set<int> s;
        for (int j = 0; j < n; j++)
            if (ll <= l[j] && rr >= r[j])
                for (int k = l[j]; k <= r[j]; k++)
                    s.insert(k);
        ans ^= s.size();
    }
    cout << ans << endl;
    return 0;
}