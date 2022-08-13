#include<iostream>
#include<windows.h>
#define LEFT 0
#define RIGHT 1 
using namespace std;
const int barWidth=50; 
int round, n;
void print_arrow(int pos, int dir) {
	int i=0;
	cout<<"[";
	if(dir==RIGHT) {
		while(i<barWidth) {
	        if (i < pos) cout << "=";
	        else if (i == pos) cout << ">";
	        else cout << " ";
			i++;			
		}
	} else if(dir==LEFT) {
		while(i<barWidth) {
	        if (i < pos) cout << " ";
	        else if (i == pos) cout << "<";
	        else cout << "=";
			i++;	
		}		
	}
	cout<<"]";
}
void running_bar() {
	round=1;
	double progress = 0.0;
	int dir=RIGHT; //从右→开始 
	int pos;
	while(round <= n) {  //round是圈数，n是目标 
		//打印进度条
		if(progress>1) dir=1-dir, progress=0; //如果达到100%了，是时侯变换方向了 
		if(dir==RIGHT)
			pos = barWidth * progress; //位置信息：总宽度*百分比 
		else
			pos = barWidth * (1-progress);
		print_arrow(pos, dir);  //打印当前状态 
		
		cout<<"小明正在跑第"<<round<<"圈"<<"\r"; 
		
	    cout.flush();  //清空输出缓存 
		progress += 0.05;  //每次更新5%，同学们可以想想多少圈一个周期 
		round++; //圈数自增一 
	    Sleep(50);  //延时50毫秒
	}
	cout<<endl;
}
int main(){
	cout<<"输入罚小明跑多少圈"<<endl; 
	cin>>n; 
	running_bar(); //使用一个我们自己写的函数 ，c100就会学到了 
	return 0;
} 


