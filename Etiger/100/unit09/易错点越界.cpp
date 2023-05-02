#include<iostream>
using namespace std;
int medals[3][4]={
    {28,30,28,86},
    {19,19,12,50},
    {17,15,20,52}
};
int main(){	
    for(int i=1;i<=3;++i){   
    	for(int j=1;j<=4;++j)
    		cout<<medals[i][j]<<" ";   
		cout<<endl; 
	}
	return 0;
} 


