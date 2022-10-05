#include <NOI>
using namespace LEARN_NOI;
int main()
{
    srand(time(NULL));
    class NOI NOI2022;
    NOI2022.algorithm["BF"].important = 10;
    NOI2022.algorithm["DaBiao"].important = 10;
    while (NOI.today < NOI.exam_date)
    {
        NOI2022.algorithm[algorithm_list[rand() % algorithm_list.size()]].learn();
        for (int i = 0; i <= 10; i++)
        {
            int current_id = NOI2022.question.done.last.id + 1;
            NOI2022.question.read_question(current_id);
            NOI2022.question.write_code(current_id);
            while (!NOI2022.question.is_done(current_id))
            {
                string submit_result = NOI2022.question.submit(current_id);
                if (submit_result == "AC")
                {
                    NOI2022.question.done.push_back(current_id);
                }
                else if (submit_result == "WA")
                {
                    NOI2022.question.write_code(current_id);
                }
                else if (submit_result == "TE")
                {
                    if (!NOI2022.question.is_enable_O2(current_id))
                    {
                        NOI2022.question.enable_O2(current_id, true);
                    }
                    else
                    {
                        NOI2022.question.optimize(current_id);
                    }
                }
                else if (submit_result == "CE")
                {
                    if (!NOI2022.question.local_compile_success(current_id))
                    {
                        NOI2022.question.skip(current_id);
                        NOI2022.question.done.push_back(current_id);
                    }
                    else
                    {
                        NOI2022.question.optimize(current_id);
                    }
                }
            }
        }
    }
    while (NOI.today == NOI.exam_date)
    {
        NOI2022.food++;
        NOI2022.water++;
        NOI2022.luck++;
        NOI2022.rp++;
        for (vector<string>::iterator sit = algorithm_list.begin(); sit != algorithm_list.end(); sit++)
            NOI2022.algorithm[*sit].remember();
    }
    return 0;
}