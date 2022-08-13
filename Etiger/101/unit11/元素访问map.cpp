// accessing mapped values
#include<iostream>
#include<map>
#include<string>
int main(){
  std::map<char,std::string> mymap;
  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];
  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';
  std::cout << "mymap now contains " << mymap.size() << " elements.\n";
  return 0;
}
/*
Notice how the last access (to element 'd') 
inserts a new element in the map with that key 
and initialized to its default value (an empty string)
even though it is accessed only to retrieve its value. 
Member function map::find does not produce this effect.
*/
