#include <bits/stdc++.h>                //万能头文件 
#include <algorithm>                    //算法库头文件 
#define N 150                            //定义最大值，120也可以 
using namespace std;                    //使用标准名字空间 
string ans[N];                            //答案 
string name[N];                            //名字 
int m, n, p[N], num = 0;                //数量等变量 
bool vst[N];                            //是否被访问过 
void print() {                            //存入数组函数 
    ans[num] = "";                        //当前项设为空 
    for (int i = 1; i <= m; i++)        //遍历每一个名字 
        ans[num] += name[p[i]];            //添加到末尾 
    ans[num] += " wang";                //添加后缀 
    num++;                                //输入数量加一 
}                                        //后括号 
void dfs(int x) {                        //枚举 
    if (x == m + 1) {                    //到了结尾 
        print();                        //存入答案数组 
        return;                            //停止程序 
    }                                    //后括号 
    for (int i = 1; i <= n; i++)        //下一项可以是每一个 
        if (!vst[i]) {                    //如果没有访问过 
            vst[i] = 1;                    //设置访问过为1 
            p[x] = i;                    //把数组的当前项设为当前数字 
            dfs(x + 1);                    //递归 
            vst[i] = 0;                    //清理现场 
        }                                //后括号 
}                                        //后括号 
int main() {                            //主函数 
    freopen("name1.in","r",stdin);
    freopen("name1.out","w",stdout);
    cin >> n;                            //输入个数 
    for (int i = 1; i <= n; i++)        //每一个名字 
        cin >> name[i];                    //输入名字 
    m = n;                                //选出个数和总个数一样 
    sort(name, name + n);                //对名字排序 
    dfs(1);                                //枚举 
    sort(ans, ans + num);                //对答案排序 
    for (int i = 0; i < num; i++)        //每一个答案 
        cout << ans[i].data() << endl;    //输出 
    return 0;                            //返回0 
}                                        //后括号 
