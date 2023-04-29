#ifndef REGEXES_HPP
#define REGEXES_HPP

#include <regex>
const std::regex REGEX_USERNAME("^[0-9a-zA-Z]{4,16}$");
const std::regex REGEX_NOT_PASSWORD("^([^a-z]+|[^A-Z]+|[^0-9]+|[a-zA-Z0-9]+)$");
const std::regex REGEX_NICKNAME("^.{4,16}$");
const std::regex REGEX_EMAIL_ADDRESS("^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(.[a-zA-Z0-9_-])+$");
const std::regex REGEX_VERIFY_CODE("^[0-9]{6}$");

#endif
