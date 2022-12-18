// 1 2
// 2 2
// 3 2
// 3 3
// 5 3
// 5 5
// 3 1
// 3 6

/*
#include<bits/stdc++.h>
using namespace std;

const int N=510,K=110;

int n,k;
struct node{
	int x,y;
	bool operator< (const node &w) const
	{
		if(x==w.x)	return y<w.y;
		return x<w.x;
		//此处为运算符重载，这里的意思就是以x为第一关键字，以y为第二关键词从小到大进行排序
	}
}a[N];
int f[N][K];

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		f[i][k]=1;
		for(int j=0;j<=k;j++)
		{
			for(int t=1;t<i;t++)
			{
				if(a[t].x>a[i].x||a[t].y>a[i].y)	continue;//要符合题意的序列限制
				int dx=abs(a[i].x-a[t].x);
				int dy=abs(a[i].y-a[t].y);
				int d=dx+dy-1;//求在x,y之间我们要加多少个自由点
				if(j+d>k)	continue;//如果要加的自由点超过k个，就不能再转移了
				f[i][j]=max(f[i][j],f[t][j+d]+d+1);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
		{
			ans=max(ans,j+f[i][j]);
			//因为我们最终可能有剩余的自由点，所以在取答案的时候，我们需要再加上剩余的自由点数量
		}
	cout<<ans;
	return 0;
}
*/
