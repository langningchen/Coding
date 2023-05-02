#include<iostream>
#include<windows.h>
using namespace std;
const int barWidth=50;
int round, n;
void running_bar() {     //自定义功能跑动进度条 
	round=1;
	double progress = 0.0;
	while(round <= n) {  //round目前圈数，n是目标 
		//打印进度条
		cout<<"[";
		progress = round*1.0/n; //算出目前圈数round占总圈数n比例 
		int pos = barWidth * progress; //将比例*总宽度barwidth，得到一个位置信息 
		int i=0;
		while(i<barWidth) {
	        if (i < pos) cout << "=";
	        else if (i == pos) cout << ">"; //002会学到这种多选一的分支语句（我们现在只会二选一） 
	        else cout << " ";
			i++;			
		}
		cout<<"] ";
		
		cout<<"小明正在跑第"<<round<<"圈"<<"\r"; 
		
	    cout.flush();  //这个神奇的函数，可以帮我们清空输出缓存 
		round++;
	    Sleep(50);  //这个神奇的函数，可以让系统睡一会儿觉（同学们可以试试如果改成其他数字会发生什么） 
	}
	cout<<endl;
}
int main(){
	cout<<"输入罚小明跑多少圈"<<endl; 
	cin>>n; 
	running_bar();
	return 0;
} 


