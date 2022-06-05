#include <bits/stdc++.h>                        //使用万能头文件见 
using namespace std;                            //使用标准名字空间 
const int N = 20;                                //定义最大值 
const int CLR = 5;                                //定义颜色数量 
char colors[CLR] = {'\0', 'A', 'B', 'C', 'D'};    //定义四种颜色 
int n, p[N];                                    //定义存颜色的数组 
void print() {                                    //输出 
    for (int i = 1; i <= n; i++)                //每一项 
        cout << colors[p[i]];                    //输出 
    cout << endl;                                //换行 
}                                                //后括号 
void dfs(int x) {                                //遍历 
    if (x == n + 1) {                            //如果到了结尾 
        print();                                 //输出 
        return;                                    //退出
    }                                             //后括号
    if (p[x] > 0) {                                //如果已固定 
        dfs(x + 1);                             //下一项 
        return;                                    //结束 
    }                                             //后括号 
    for (int i = 1; i < CLR; i++)                //每一个颜色 
        if (x == 1 && p[2] != i ||                //如果是第一个 
            x == n && p[x - 1] != i ||            //如果是最后一个 
            p[x - 1] != i && p[x + 1] != i) {    //如果是中间 
            p[x] = i;                            //颜色数组设为该颜色 
            dfs(x + 1);                            //下一层 
            p[x] = 0;                            //恢复现场 
        }                                        //后括号
}                                                //后括号
int main() {
    freopen("color2.in","r",stdin);
    freopen("color2.out","w",stdout);
    char ch;                                    //定义输入
    while (cin >> ch) {                            //输入 
        ++n;                                    //个数增加一 
        if (ch == 'A')                            //如果是B 
            p[n] = 1;                            //设为1 
        else if (ch == 'B')                        //如果是G 
            p[n] = 2;                            //设为2 
        else if (ch == 'C')                        //如果是R 
            p[n] = 3;                            //设为3 
        else if (ch == 'D')                        //如果是R 
            p[n] = 4;                            //设为3 
        else p[n] = 0;                            //未定设为0 
    }                                            //后括号
    dfs(1);                                        //遍历 
    return 0;                                    //返回0 
}                                                //后括号
