#include <iostream>
#include <fstream>
#include <termio.h>
#include <unistd.h>
#include "configor/json.hpp"
#include "StringOperation.hpp"
using namespace std;
using namespace configor;
int main()
{
    srand(time(NULL));
    json Data = json::parse(GetDataFromFileToString("Projects/English Review/Data.json"));
    string QuestionSet = "My daily life";
    while (1)
    {
        system("clear");
        int Index = rand() % Data[QuestionSet].size();
        cout << Data[QuestionSet][Index]["Chinese"].as_string() << endl;
        for (size_t i = 0; i < Data[QuestionSet][Index]["English"].size(); i++)
        {
            for (size_t j = 0; j < Data[QuestionSet][Index]["English"][i].as_string().size(); j++)
            {
                if ((Data[QuestionSet][Index]["English"][i].as_string()[j] >= 'a' && Data[QuestionSet][Index]["English"][i].as_string()[j] <= 'z') ||
                    (Data[QuestionSet][Index]["English"][i].as_string()[j] >= 'A' && Data[QuestionSet][Index]["English"][i].as_string()[j] <= 'Z'))
                    cout << "_";
                else
                    cout << Data[QuestionSet][Index]["English"][i].as_string()[j];
            }
            cout << endl;
            string Input;
            getline(cin, Input);
            if (Input != Data[QuestionSet][Index]["English"][i].as_string())
            {
                cout << Data[QuestionSet][Index]["English"][i].as_string() << endl;
                Data[QuestionSet][Index]["ErrorCount"] = Data[QuestionSet][Index]["ErrorCount"].as_integer() + 1;
                getchar();
            }
        }
        Data[QuestionSet][Index]["Count"] = Data[QuestionSet][Index]["Count"].as_integer() + 1;
        ofstream OutputFileStream("/mnt/d/01_8A/03_英语/默写.json");
        OutputFileStream << Data.dump(4, ' ');
        OutputFileStream.close();
    }
    return 0;
}
