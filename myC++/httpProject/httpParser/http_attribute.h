#ifndef __HTTPPROJECT_HTTP_ATTRIBUTE_H__
#define __HTTPPROJECT_HTTP_ATTRIBUTE_H__


#include<unordered_map>
#include<string>
#include<memory>
#include<iostream>

#include "http_request_code.h"
#include "request_parser.h"
#include "request_line_parser.h"
#include "request_head_parser.h"
#include "request_content_parser.h"

namespace http_project
{

class http_attribute
{
private:
    using parser_code = http_request_code::parser_code;
    using state = http_request_code::state;
    using http_code = http_request_code::http_code;

public:
    http_attribute(const std::string &content);
    ~http_attribute(){}
    void add_content(const std::string& content);
    state get_http_request_code();
    void parsering();

private:
    std::string buffer;
    std::string::size_type idx;
    std::unordered_map<std::string, std::string>attribute;
    std::shared_ptr<request_parser>parser_obj;
    parser_code parser_result;
    state result;

};

http_attribute::http_attribute(const std::string& content):
buffer(content), idx(0), parser_result(http_request_code::PARSER_ING),
result(state::CHECK_STATE_REQUESTLINE), parser_obj(nullptr)
{
    parsering();
}

void http_attribute::add_content(const std::string &content)
{
    buffer += content;
    //std::cout << buffer << std::endl;
    parsering();
}

http_attribute::state http_attribute::get_http_request_code()
{
    for(auto iter = attribute.begin(); iter != attribute.end(); ++iter)
    {
        std::cout << iter->first << ": " << iter->second << std::endl;
    }

    return result;
}

void http_attribute::parsering()
{
    if(parser_result == parser_code::PARSER_ERROR)return;//output a error
    if(result == state::CHECK_STATE_REQUESTLINE)
    {

        parser_obj = std::make_shared<request_line_parser>(request_line_parser());
        parser_result = parser_obj->parser(attribute, buffer, idx);
        if(parser_result == parser_code::PARSER_SUCCESS)
        {
            std::cout << "request line parser success" << std::endl;
            result = state::CHECK_STATE_REQUESTHEAD;
        }
        else return;
    }
    if(result == state::CHECK_STATE_REQUESTHEAD)
    {
        
        parser_obj = std::make_shared<request_head_parser>(request_head_parser());
        parser_result = parser_obj->parser(attribute, buffer, idx);
        if(parser_result == parser_code::PARSER_SUCCESS)
        {
            std::cout << "request head parser success" << std::endl;
            result = state::CHECK_STATE_REQUESTCONTENT;
        }
        else return;
    }

    if(result == state::CHECK_STATE_REQUESTCONTENT)
    {
        
        parser_obj = std::make_shared<request_content_parser>(request_content_parser());
        parser_result = parser_obj->parser(attribute, buffer, idx);
        if(parser_result == parser_code::PARSER_SUCCESS)
        {
            std::cout << "request content parser success" << std::endl;
            result = state::CHECK_STATE_FINISH;
        }
        else return;
    }
}


};


#endif