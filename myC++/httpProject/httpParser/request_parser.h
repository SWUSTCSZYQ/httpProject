#ifndef __HTTPPROJECT_REQUEST_PARSER_H__
#define __HTTPPROJECT_REQUEST_PARSER_H__

#include<unordered_map>
#include<string>
#include "http_request_code.h"

namespace http_project{

class request_parser{

public:
    request_parser() = default;
    virtual ~request_parser() = 0;
    virtual http_request_code::parser_code parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type &idx) = 0;
};

request_parser::~request_parser(){}

};
#endif