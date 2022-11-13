#include "../Lib/String.cpp"
using namespace std;
int main()
{
    String s;
    s = "12";
    String s2;
    s2 = s;
    s2 += "34";
    cout << s2 << endl;
    cout << s2.substr(3, 3) << " " << s2.substring(3, 6) << endl;
    cout << s2.find("123") << " " << s2.find("234") << " " << s2.find("345") << endl;
    s2.insert(2, "23");
    cout << s2 << " ";
    s2.erase(2, 2);
    cout << s2 << " ";
    s2.replace(2, 2, "12");
    cout << s2 << " ";
    s2.replace("12", "34");
    cout << s2 << " ";
    s2 = s;
    cout << s2 << endl;
    String s3;
    s3 = "12345";
    cout << (s2 < s3) << " " << (s2 <= s3) << " " << (s2 == s3) << " " << (s2 >= s3) << " " << (s2 > s3) << " " << (s2 != s3) << endl;
    s3 = "123455";
    cout << (s2 < s3) << " " << (s2 <= s3) << " " << (s2 == s3) << " " << (s2 >= s3) << " " << (s2 > s3) << " " << (s2 != s3) << endl;
    s3 = "123456";
    cout << (s2 < s3) << " " << (s2 <= s3) << " " << (s2 == s3) << " " << (s2 >= s3) << " " << (s2 > s3) << " " << (s2 != s3) << endl;
    s3 = "123457";
    cout << (s2 < s3) << " " << (s2 <= s3) << " " << (s2 == s3) << " " << (s2 >= s3) << " " << (s2 > s3) << " " << (s2 != s3) << endl;
    s3 = "1234567";
    cout << (s2 < s3) << " " << (s2 <= s3) << " " << (s2 == s3) << " " << (s2 >= s3) << " " << (s2 > s3) << " " << (s2 != s3) << endl;
    return 0;
}
