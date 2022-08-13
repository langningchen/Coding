#include<iostream>
#include<string>
#include<sstream>
#include<ctime> 
#include<cstdlib>
#define M 5
using namespace std;
string greet[M]={"*** 输出回答：你好少年 ***",
				"*** 输出回答：地球人你好 ***",
				"*** 输出回答：有啥吩咐？ ***",
				"*** 输出回答：请问我问题 ***",
				"*** 输出回答：呵呵 ***"}; 				 
string joke[M]={"    小明买了一本教人如何快速睡着的书，天天看到天亮。***",
				"    我是内蒙古的海军总司令 ***",
				"    法官：你为什么要印假钞？\n    被告无辜地说：因为我不会印真钞。 ***",
				"    贼甲：快数数今天一共抢了多少钱？\n    贼乙：不用，明天看看报纸就知道了。 ***",
				"    妈妈：你的拿手好菜是什么？\n    小红：我烧的...白开水还不错！ *** "};
string sorry[M]={"*** 输出回答：不好意思，我的智商太低听不懂 ***",
				"*** 输出回答：让我想想 ***",
				"*** 输出回答：这个问题我不准备回答 ***",
				"*** 输出回答：无可奉告 ***",
				"*** 输出回答：下次再告诉你 ***"};
bool allDigits(string s){
	for(int i=0;i<s.size();i++)
		if(s[i]<'0'||s[i]>'9') return 0;
	return 1;
}

void decompose(string s){
	stringstream ss;
	int n,c=0;
	ss<<s; ss>>n;
	if(n<=1) {cout<<"    这个数太小了"<<n<<"我好像分解不了 ***"<<endl;return;} 
	for(int i=2;i*i<=n;i++)
		while(n%i==0){
			if(c==0) {cout<<"    看看我分解的结果吧，我知道：n等于"<<i; c++;} 
			else cout<<"乘以"<<i;
			n/=i;
		}
	if(c==0) cout<<"    而且我还知道"<<n<<"是个质数呢 ***"<<endl;
	else if(n>1) cout<<"乘以"<<n<<" ***"<<endl;
	else cout<<" ***"<<endl;
}

int main(){
	cout<<endl;
	cout<<"--------------机器人使用说明书--------------"<<endl;
	cout<<endl;
	cout<<" 你好，我是聊天机器人，你可以问我各种问题"<<endl;
	cout<<" 请调换到中文输入法，鼠标点击唤醒本窗口"<<endl; 
	cout<<" 你可以在下方光标处随意打字提问"<<endl; 
	cout<<" 提好问后，请按enter键，发送到机器人程序里"<<endl;
	cout<<" 如果程序知道答案，它会把回答显示到窗口下一行"<<endl;
	cout<<" 它跳出答案后，你可以在光标处向它继续提问"<<endl;
	cout<<endl; 
	cout<<"--------------------------------------------"<<endl;
	cout<<endl; 
	while(1){
		string s;
		getline(cin,s);
		if(s=="") continue;
		if(s=="88") 
			break; 
		else if(s.find("名")!=-1||s.find("谁")!=-1) 
			cout<<"*** 输出回答：我的名字叫MIKE，你是我的主人 ***"<<endl; 
		else if(s.find("岁")!=-1||s.find("多大")!=-1)
			cout<<"*** 输出回答：我今年100岁了，我永远不会死 ***"<<endl;	
		else if(s.find("哪里")!=-1||s.find("哪儿")!=-1)	
			cout<<"*** 输出回答：无处不在 ***"<<endl; 
		else if(s.find("会")!=-1||s.find("特长")!=-1)
			cout<<"*** 输出回答：我什么都不会，只会聊天 ***"<<endl;
		else if(s.find("生")!=-1)
			cout<<"*** 输出回答：我生日是2月29日，请送我生日礼物吧 ***"<<endl;
		else if(s.find("智")!=-1)
			cout<<"*** 输出回答：我的智商为59，还没有及格 ***"<<endl;
		else if(s.find("球")!=-1||s.find("兴")!=-1||s.find("爱")!=-1)
			cout<<"*** 输出回答：我爱看足球，但是不能踢足球，因为我没有腿 ***"<<endl;
		else if(s.find("笑")!=-1)
			cout<<"*** 输出回答：我来给你说个笑话吧："<<endl<<joke[rand()%M]<<endl;
		else if(s.find("你好")!=-1)
			cout<<greet[rand()%M]<<endl;
		else if(allDigits(s)){
			cout<<"*** 输出回答："<<s<<"是个好数字"<<endl;
			decompose(s); 
		}
		else 
			cout<<sorry[rand()%M]<<endl;	
	}
	cout<<endl; 
	cout<<"-------------你触发了结束的机关-------------"<<endl;
	cout<<" 重要通知： "<<endl; 
	cout<<" 程序运行结束，请按任意键，窗口将自动关闭 "<<endl;   
	cout<<" （请不要理会下方密文，它们只是系统信息） "<<endl; 
	cout<<endl; 
	cout<<" 再见！我要继续听课啦！ "<<endl;
	cout<<"--------------------------------------------"<<endl;
	return 0;
}


