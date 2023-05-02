#include<iostream>
#include<ctime> 
#include<windows.h>
using namespace std;
void SLEEP(int x){ //—” ±x∫¡√Î 
	clock_t now=clock(); 
	while(clock()-now<x); 
} 
int main(){
	system("color a");
	string boom1="            --_--\n         (  -_    _).\n       ( ~       )   )\n     (( )  (    )  ()  )\n      (.   )) (       )\n        ``..     ..``\n             | |\n           (=| |=)\n             | |\n         (../( )\\.))";
	string boom2="              ________________\n         ____/ (  (    )   )  \\___\n        /( (  (  )   _    ))  )   )\\\n      ((     (   )(    )  )   (   )  )\n    ((/  ( _(   )   (   _) ) (  () )  )\n   ( (  ( (_)   ((    (   )  .((_ ) .  )_\n  ( (  )    (      (  )    )   ) . ) (   )\n (  (   (  (   ) (  _  ( _) ).  ) . ) ) ( )\n ( (  (   ) (  )   (  ))     ) _)(   )  )  )\n( (  ( \\ ) (    (_  ( ) ( )  )   ) )  )) ( )\n (  (   (  (   (_ ( ) ( _    )  ) (  )  )   )\n( (  ( (  (  )     (_  )  ) )  _)   ) _( ( )\n ((  (   )(    (     _    )   _) _(_ (  (_ )\n  (_((__(_(__(( ( ( |  ) ) ) )_))__))_)___)\n  ((__)        \\\\||lll|l||///          \\_))\n           (   /(/ (  )  ) )\\   )\n         (    ( ( ( | | ) ) )\\   )\n          (   /(| / ( )) ) ) )) )\n        (     ( ((((_(|)_)))))     )\n         (      ||\\(|(|)|/||     )\n       (        |(||(||)||||        )\n         (     //|/l|||)|\\\\ \\     )\n       (/ / //  /|//||||\\\\  \\ \\  \\ _)";
	int tm=10;
	while(tm>0) {
		cout<<"   "<<tm<<endl;
		SLEEP(1000);
		system("cls");
		tm--;
	} 
	cout<<boom1;
	SLEEP(3000);
	system("cls");
	cout<<boom2;
	return 0;
}



