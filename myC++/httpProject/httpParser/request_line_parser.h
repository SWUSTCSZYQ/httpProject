#ifndef __HTTPPROJECT_REQUEST_LINE_PARSER_H__
#define __HTTPPROJECT_REQUEST_LINE_PARSER_H__

#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>
#include<algorithm>
#include "request_parser.h"


namespace http_project
{

class request_line_parser: public request_parser
{
public:
    request_line_parser();
    ~request_line_parser(){}
    http_request_code::parser_code parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type& idx);

private:
    std::unordered_set<std::string>methods;
    std::vector<std::string>attr;
};

request_line_parser::request_line_parser():
attr({"method", "http_addr", "protocol"}),
methods({"GET", "POST", "HEAD", "DELETE", "OPTIONS", "PUT", "TRACE", "CONNECT"})
{

}


http_request_code::parser_code request_line_parser::parser(std::unordered_map<std::string, std::string>&http_attribute, const std::string &content, std::string::size_type &idx)
{
    std::string::size_type m_idx = idx;
    for(; m_idx < content.length() - 1; ++m_idx)
    {
        if(content[m_idx] == '\r' and content[m_idx + 1] == '\n')break;
    }
    if(m_idx == content.length() - 1)return http_request_code::PARSER_ING;//not a complete line
    std::string tmp = "";
    int space_num = 0;
    std::string::size_type i = 0;
    while(i <= m_idx)
    {
        if(content[i] == ' ' or i == m_idx)
        {
            if((space_num == 0 and !methods.count(tmp)) or (space_num == 2 and tmp != "HTTP/1.1"))return http_request_code::PARSER_ERROR;//parser_error
            http_attribute[attr[space_num]] = tmp;
            ++space_num;
            tmp = "";
            ++i;
        }
        else tmp += content[i++];
    }
    idx = m_idx + 2;
    return http_request_code::PARSER_SUCCESS;
    
}


};

#endif