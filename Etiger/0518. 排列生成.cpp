#include <iostream>                        //输入输出流 
#define N 30                            //定义最大值 
using namespace std;                    //使用标准名字空间 
int m, n, p[N];                            //定义变量 
bool vst[N];                            //是否被访问过 
void print() {                            //输出 
    for (int i = 1; i <= m - 1; i++)    //每一个数 
        cout << p[i] << " ";            //输出 
    cout << p[m] << endl;                //防止行末有空格 
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
    cin >> n;                            //输入 
    m = n;                                //选出个数和总个数一样 
    dfs(1);                                //枚举 
    return 0;                            //返回0 
}                                        //后括号 
