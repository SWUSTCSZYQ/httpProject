#ifndef __HTTPPROJECT_REQUEST_HEAD_PARSER_H__
#define __HTTPPROJECT_REQUEST_HEAD_PARSER_H__

#include<unordered_map>
#include<string>
#include<assert.h>
#include "request_parser.h"

namespace http_project{

class request_head_parser:public request_parser
{

public:
    request_head_parser() = default;
    ~request_head_parser(){}
    http_request_code::parser_code parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type &idx);
};

http_request_code::parser_code request_head_parser::parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type &idx)
{
    assert(http_attribute.count("method")); // request line has been parsered
    std::string::size_type m_idx = idx;
    while(m_idx < content.length() - 1 and content[m_idx] != '\r' and content[m_idx + 1] != '\n')
        ++m_idx;

    if(m_idx == content.length() - 1)
        return http_request_code::PARSER_ING; // not a complete line

    if(content[idx] == '\r' and content[idx + 1] == '\n')
    {
        http_attribute["request_head_parser_finished"] = "";
        return http_request_code::PARSER_SUCCESS;
    }

    std::string::size_type i = idx;
    std::string key = "";
    std::string value = "";
    while(i < m_idx and content[i] != ':')key += content[i++];
    if(i == m_idx)return http_request_code::PARSER_ERROR;
    ++i; // a space
    while(++i < m_idx)value += content[i];
    http_attribute[key] = value;

    idx = m_idx + 2;
    return parser(http_attribute, content, idx);
}


};

#endif