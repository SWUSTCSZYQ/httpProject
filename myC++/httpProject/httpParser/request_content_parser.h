#ifndef __HTTPPROJECT_REQUEST_CONTENT_PARSER_H__
#define __HTTPPROJECT_REQUEST_CONTENT_PARSER_H__


#include "request_parser.h"
#include "assert.h"

namespace http_project{

class request_content_parser:public request_parser
{

public:
    request_content_parser() = default;
    ~request_content_parser(){}
    http_request_code::parser_code parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type& idx);

};

http_request_code::parser_code request_content_parser::parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type &idx)
{
    assert(http_attribute.count("request_head_parser_finished")); // request head has been parsered
}


};

#endif