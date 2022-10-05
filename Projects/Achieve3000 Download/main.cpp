#include "../../lib/Curl.cpp"
#include <regex>
#include <unistd.h>
string StringReplaceAll(string Data, string Before, string After)
{
    size_t FoundedPos;
    while ((FoundedPos = Data.find(Before)) != Data.npos)
    {
        Data.replace(FoundedPos, Before.size(), After);
    }
    return Data;
}
string NormalizeString(string Data)
{
    Data = regex_replace(Data, regex("(<[/]?[^>]*>|\n|\t)"), "");
    Data = StringReplaceAll(Data, "\n", "");
    Data = StringReplaceAll(Data, "\t", "");
    return Data;
}
int main()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    readlink("/proc/self/exe", Buffer, BufferSize);
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, CurrentDir.npos);

    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");
    GetDataToFile("https://portal.achieve3000.com/util/login.php", "Header.tmp", "Body.tmp", true, "debug=0&login_goto=&lang=1&ajax_yn=Y&flash_version=&login_name=langning.chen&wz=0&cli=0&login_url=portal.achieve3000.com%2Findex&password=special&cdn=VIDEOCDN%3A0%3BAUDIOCDN%3A0%3BIMAGECDN%3A0%3BDOCSCDN%3A0%3BIMAGEASSETSCDN%3A0%3BAPPASSETSCDN%3A0%3BJSASSETSCDN%3A0%3BCSSASSETSCDN%3A0&banner=1&redirectedFromLE=&login_page_type=&domain_id=1&walkme=&lid=&login_error_message=&login_name1=&password1=&lost_login_name=&isAjax=Y", NULL, NULL, "application/x-www-form-urlencoded; charset=UTF-8");
    GetDataToFile("https://portal.achieve3000.com/my_lessons");
    string HTMLData = GetDataFromFileToString();
    vector<pair<string, pair<string, string>>> Lessons;
    smatch Match;
    string::const_iterator StartPos = HTMLData.cbegin();
    while (regex_search(StartPos, HTMLData.cend(), Match, regex("<a class=\"title\" href=\"/lesson\\?lid=([0-9]*)&c=([0-9]*)&sc=([0-9]*)&oid=[0-9]*&ot=[0-9]*&asn=[0-9]*\"  >[^<]*</a>\n\t<div>\n\t\t[^5]*5-Step Lesson</span></div>")))
    {
        Lessons.push_back(make_pair(Match.str(1), make_pair(Match.str(2), Match.str(3))));
        StartPos = Match.suffix().first;
    }
    int Counter = 1;
    for (vector<pair<string, pair<string, string>>>::iterator vit = Lessons.begin(); vit != Lessons.end(); vit++)
    {
        GetDataToFile(string("https://portal.achieve3000.com/api/v1/lessoncontent/fetch?lid=" + vit->first + "&c=" + vit->second.first + "&sc=" + vit->second.second).c_str());
        json Data = json::parse(GetDataFromFileToString());
        cout << "#" << Counter << "  " << NormalizeString(Data["lessonInfo"]["lessonName"]) << endl
             << NormalizeString(Data["lessonInfo"]["lessonSummary"]) << endl
             << NormalizeString(Data["lessonInfo"]["categoryName"]) << ": " << NormalizeString(Data["lessonInfo"]["subCategoryName"]) << endl
             << endl;
        Counter++;
    }
    int Index;
    cout << "Please input the id: ";
    cin >> Index;
    if (Index >= Counter)
    {
        cout << "Input invalid" << endl;
        return 0;
    }

    string LessonID = Lessons[Index - 1].first;
    string CategoryID = Lessons[Index - 1].second.first;
    string SubcategoryID = Lessons[Index - 1].second.second;
    GetDataToFile(string("https://portal.achieve3000.com/api/v1/lessoncontent/fetch?lid=" + LessonID + "&c=" + CategoryID + "&sc=" + SubcategoryID).c_str());
    json Data = json::parse(GetDataFromFileToString());
    HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-ACHIEVE-SESSION: " + Data["session"]["resumeSessionId"].as_string()).c_str());
    HeaderList = curl_slist_append(HeaderList, string("X-ACHIEVE-SESSION-KEY: " + Data["session"]["resumeSessionToken"].as_string()).c_str());
    HeaderList = curl_slist_append(HeaderList, string("X-XSRF-TOKEN: " + Data["session"]["csrfToken"].as_string()).c_str());
    GetDataToFile(string("https://portal.achieve3000.com/api/v1/lessonactivity/fetch?lesson_id=" + LessonID + "&category_id=" + CategoryID + "&step_id=14&progress=true").c_str(), "Header.tmp", "Body.tmp", false, "", HeaderList);
    json QuestionData = json::parse(GetDataFromFileToString());
    string FileName = regex_replace(NormalizeString(Data["lessonInfo"]["lessonName"].as_string()), regex("(\\?|\"|/|\\|\\|<|>|:|\\*)"), "");
    ofstream OutputFileStream("/mnt/c/Users/Son/Desktop/" + FileName + ".html");
    OutputFileStream << "<html>" << endl
                     << "<head>" << endl
                     << "  <title>" << endl
                     << "    " << NormalizeString(Data["lessonInfo"]["lessonName"].as_string()) << endl
                     << "  </title>" << endl
                     << "  <style>" << endl
                     << "    * {" << endl
                     << "      font-size: 15px;" << endl
                     << "    }" << endl
                     << "    .Big1," << endl
                     << "    .Big2," << endl
                     << "    .Big3 {" << endl
                     << "      font-weight: 600;" << endl
                     << "    }" << endl
                     << "    .Big1 {" << endl
                     << "      font-size: 25px;" << endl
                     << "    }" << endl
                     << "    .Big2 {" << endl
                     << "      font-size: 20px;" << endl
                     << "    }" << endl
                     << "    .Big3 {" << endl
                     << "      font-size: 18px;" << endl
                     << "    }" << endl
                     << "    .Code," << endl
                     << "    .CodeBlock {" << endl
                     << "      border-radius: 3px;" << endl
                     << "      background-color: rgba(0, 0, 0, 0.05);" << endl
                     << "      padding: 2px 5px;" << endl
                     << "      color: black;" << endl
                     << "    }" << endl
                     << "    .CodeBlock {" << endl
                     << "      border-radius: 10px;" << endl
                     << "      width: 100%;" << endl
                     << "    }" << endl
                     << "    .CheckBox {" << endl
                     << "      vertical-align: middle;" << endl
                     << "      height: 20px;" << endl
                     << "      width: 20px;" << endl
                     << "    }" << endl
                     << "    hr {" << endl
                     << "      height: 4px;" << endl
                     << "      background-color: rgba(0, 0, 0, 0.3);" << endl
                     << "      border-style: none;" << endl
                     << "      margin: 20px 0px;" << endl
                     << "      border-radius: 3px;" << endl
                     << "    }" << endl
                     << "  </style>" << endl
                     << "</head>" << endl
                     << "<body>" << endl
                     << "  <span class=\"Big1\">" << endl
                     << "    " << NormalizeString(Data["lessonInfo"]["lessonName"].as_string()) << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl
                     << "  <span class=\"Big2\">" << endl
                     << "    Ready" << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl
                     << "  <span>" << endl;
    string PollQuestion = Data["poll"]["question"].as_string();
    PollQuestion = regex_replace(PollQuestion, regex("<[/]?[^>]*>"), "");
    OutputFileStream << "    " << PollQuestion << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <span>" << endl
                     << "    " << Data["poll"]["opinionStatement"].as_string() << endl
                     << "  </span>" << endl
                     << "  <br />" << endl;
    for (json::iterator jit = Data["poll"]["choices"].begin(); jit != Data["poll"]["choices"].end(); jit++)
    {
        OutputFileStream << "  <input type=\"checkbox\" class=\"CheckBox\" />" << endl
                         << "  <span>" << endl
                         << "    " << jit.value()["choiceText"].as_string() << endl
                         << "  </span>" << endl
                         << "  <br />" << endl;
    }
    OutputFileStream << "  <span>" << endl
                     << "    Explain why you voted the way you did. " << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl
                     << "  <div class=\"CodeBlock\">" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "  </div>" << endl
                     << "  <hr />" << endl
                     << "  <span class=\"Big2\">" << endl
                     << "    Vocabulary" << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl;
    for (json::iterator jit = Data["lessonContent"]["vocabulary"].begin(); jit != Data["lessonContent"]["vocabulary"].end(); jit++)
    {
        OutputFileStream << "  <span class=\"Big3\">" << endl
                         << "    <span>" << endl
                         << "      " << jit.value()["word"].as_string() << endl
                         << "    </span>" << endl
                         << "    <span class=\"Code\">" << endl
                         << "      " << jit.value()["speechPart"].as_string() << endl
                         << "    </span>" << endl
                         << "  </span>" << endl
                         << "  <br />" << endl
                         << "  <span>" << endl
                         << "    " << jit.value()["definition"].as_string() << endl
                         << "  </span>" << endl
                         << "  <br />" << endl;
    }
    OutputFileStream << "  <hr />" << endl
                     << "  <span class=\"Big2\">" << endl
                     << "    Read" << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl;
    string Article = Data["lessonContent"]["articles"][0]["pages"][0]["content"].as_string();
    Article = regex_replace(Article, regex("<em>[a-zA-Z\\s]* contributed to this story.</em>"), "");
    Article = regex_replace(Article, regex("Credit for photo and all related images: [^<]*"), "");
    Article = regex_replace(Article, regex("<[/]?(span|br|video|p|div)[^>]*>"), "");
    Article = regex_replace(Article, regex("<a class='dict-word' href='#' title='Show dictionary definition'>[a-zA-Z\\s]*</a>"), "");
    Article = regex_replace(Article, regex("<!--.*-->"), "");
    vector<string> PictureVector;
    StartPos = Article.cbegin();
    while (regex_search(StartPos, Article.cend(), Match, regex("<img[^>]*src=\"([^\"]*)\"[^>]*>")))
    {
        PictureVector.push_back(Match.str(1));
        StartPos = Match.suffix().first;
    }
    Article = regex_replace(Article, regex("<img[^>]*src=\"([^\"]*)\"[^>]*>"), "");
    Article = StringReplaceAll(Article, "\t", "");
    Article = StringReplaceAll(Article, " \n", "\n");
    Article = StringReplaceAll(Article, "\n ", "\n");
    Article = StringReplaceAll(Article, "\n\n\n", "\n\n");
    while (Article.size() > 0 && Article[Article.size() - 1] == '\n')
        Article.erase(Article.size() - 1, 1);
    while (Article.size() > 0 && Article[0] == '\n')
        Article.erase(0, 1);
    Article = StringReplaceAll(Article, "\n\n", "\n  </span>\n  <br />\n  <span>\n    ");
    Article = "  <span>\n    " + Article + "\n  </span>";
    OutputFileStream << Article << endl
                     << "  <br />" << endl;
    for (vector<string>::iterator vit = PictureVector.begin(); vit != PictureVector.end(); vit++)
        if (vit->find("magnify") == vit->npos && vit->size() > 1)
        {
            string URL = *vit;
            if (URL[0] != 'h')
                URL.insert(0, "https://portal.achieve3000.com");
            OutputFileStream << "  <img src=\"" << URL << "\" style=\"width: 48%; \"/>" << endl;
        }
    OutputFileStream << "  <hr />" << endl
                     << "  <span class=\"Big2\">" << endl
                     << "    Respond" << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl;
    Counter = 0;
    for (json::iterator jit = QuestionData["activities"][0]["questions"].begin(); jit != QuestionData["activities"][0]["questions"].end(); jit++)
    {
        OutputFileStream << "  <span class=\"Big3\">" << endl
                         << "    Question " << Counter + 1 << endl
                         << "  </span>" << endl
                         << "  <br />" << endl;
        string Question = jit.value()["collection"][0]["question"].as_string();
        Question = regex_replace(Question, regex("<[/]?(span|br|video|p|div|a)[^>]*>"), "");
        Question = regex_replace(Question, regex("<img[^>]*src=\"([^\"]*)\"[^>]*>"), "<img src=\"https://portal.achieve3000.com$1\" style=\"width: 48%; \">");
        Question = StringReplaceAll(Question, "\t", "");
        Question = StringReplaceAll(Question, " \n", "\n");
        Question = StringReplaceAll(Question, "\n ", "\n");
        Question = StringReplaceAll(Question, "\n\n\n", "\n\n");
        while (Question.size() > 0 && Question[Question.size() - 1] == '\n')
            Question.erase(Question.size() - 1, 1);
        while (Question.size() > 0 && Question[0] == '\n')
            Question.erase(0, 1);
        Question = StringReplaceAll(Question, "\n\n", "\n  </span>\n  <br />\n  <span>\n    ");
        Question = "  <span>\n    " + Question + "\n  </span>";
        OutputFileStream << Question << endl
                         << "  <br />" << endl;
        short Counter2 = 0;
        for (json::iterator jit2 = QuestionData["activities"][0]["questions"][Counter]["collection"][0]["items"].begin(); jit2 != QuestionData["activities"][0]["questions"][Counter]["collection"][0]["items"].end(); jit2++)
        {
            string Item = jit2.value()["label"].as_string();
            Item = regex_replace(Item, regex("<div.*class=\"screenreader-only\">[^<]*</div>"), "");
            Item = regex_replace(Item, regex("<[/]?(span|br|video|p|div|a)[^>]*>"), "");
            Item = StringReplaceAll(Item, "\t", "");
            Item = StringReplaceAll(Item, " \n", "\n");
            Item = StringReplaceAll(Item, "\n ", "\n");
            Item = StringReplaceAll(Item, "\n\n\n", "\n\n");
            while (Item.size() > 0 && Item[Item.size() - 1] == '\n')
                Item.erase(Item.size() - 1, 1);
            while (Item.size() > 0 && Item[0] == '\n')
                Item.erase(0, 1);
            Item = StringReplaceAll(Item, "\n\n", "\n    </span>\n    <br />\n    <span>\n      ");
            Item = "    <span>\n      " + Item + "\n    </span>";
            OutputFileStream << "  <input type=\"checkbox\" class=\"CheckBox\" />" << endl
                             << "  <span>" << endl
                             << "    <span>" << endl
                             << "      " << (char)(Counter2 + 'A') << ".&ensp;" << endl
                             << "    </span>" << endl
                             << Item << endl
                             << "  </span>" << endl
                             << "  <br />" << endl;
            Counter2++;
        }
        OutputFileStream << "  <br />" << endl;
        Counter++;
    }
    OutputFileStream << "  <hr />" << endl
                     << "  <span class=\"Big2\">" << endl
                     << "    Reflect" << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl
                     << "  <span>" << endl
                     << "    " << PollQuestion << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <span>" << endl
                     << "    " << Data["poll"]["opinionStatement"].as_string() << endl
                     << "  </span>" << endl
                     << "  <br />" << endl;
    for (json::iterator jit = Data["poll"]["choices"].begin(); jit != Data["poll"]["choices"].end(); jit++)
    {
        OutputFileStream << "  <input type=\"checkbox\" class=\"CheckBox\" />" << endl
                         << "  <span>" << endl
                         << "    " << jit.value()["choiceText"].as_string() << endl
                         << "  </span>" << endl
                         << "  <br />" << endl;
    }
    OutputFileStream << "  <span>" << endl
                     << "    Explain why you voted the way you did. " << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl
                     << "  <div class=\"CodeBlock\">" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "  </div>" << endl
                     << "  <hr />" << endl
                     << "  <span class=\"Big2\">" << endl
                     << "    Write" << endl
                     << "  </span>" << endl
                     << "  <br />" << endl
                     << "  <br />" << endl;
    string WritingQuestion = Data["thoughtQuestion"]["question"].as_string();
    WritingQuestion = regex_replace(WritingQuestion, regex("<[/]?(span|br|video|p|div|a)[^>]*>"), "");
    WritingQuestion = StringReplaceAll(WritingQuestion, "\t", "");
    WritingQuestion = StringReplaceAll(WritingQuestion, " \n", "\n");
    WritingQuestion = StringReplaceAll(WritingQuestion, "\n ", "\n");
    WritingQuestion = StringReplaceAll(WritingQuestion, "\n\n\n", "\n\n");
    while (WritingQuestion.size() > 0 && WritingQuestion[WritingQuestion.size() - 1] == '\n')
        WritingQuestion.erase(WritingQuestion.size() - 1, 1);
    while (WritingQuestion.size() > 0 && WritingQuestion[0] == '\n')
        WritingQuestion.erase(0, 1);
    WritingQuestion = StringReplaceAll(WritingQuestion, "\n\n", "\n  </span>\n  <br />\n  <span>\n    ");
    WritingQuestion = "  <span>\n    " + WritingQuestion + "\n  </span>";
    OutputFileStream << WritingQuestion << endl
                     << "  <br />" << endl
                     << "  <br />" << endl
                     << "  <div class=\"CodeBlock\">" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "    <br />" << endl
                     << "  </div>" << endl
                     << "  <script>" << endl
                     << "    window.print();" << endl
                     << "    setTimeout(function() {" << endl
                     << "	      window.close();" << endl
                     << "    }, 1500);" << endl
                     << "  </script>" << endl
                     << "</body>" << endl
                     << "</html>" << endl;
    system(string("\"/mnt/c/Program Files/Google/Chrome/Application/chrome.exe\" --kiosk-printing --kiosk \"C:\\Users\\Son\\Desktop\\" + FileName + ".html\"").c_str());
    char DeleteOrNot;
    cout << "Delete to html file(y=Yes other=No)? ";
    cin >> DeleteOrNot;
    if (DeleteOrNot == 'y' || DeleteOrNot == 'Y')
        system(string(string("rm -f /mnt/c/Users/Son/Desktop/") + FileName + ".html").c_str());
    return 0;
}