#include "Result.hpp"

RESULT::RESULT()
{
    Success = true;
    Message = "No message";
}
RESULT::RESULT(bool Success, std::string Message)
{
    this->Success = Success;
    this->Message = Message;
}
