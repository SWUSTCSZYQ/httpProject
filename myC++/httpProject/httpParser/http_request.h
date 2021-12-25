#ifndef __HTTPPROJECT_HTTP_REQUEST_H__
#define __HTTPPROJECT_HTTP_REQUEST_H__

#include<string>
#include<memory>
#include "http_request_code.h"
#include "http_attribute.h"

namespace http_project{

class http_request{

private:
    std::string content; //http content
    std::shared_ptr<http_attribute> parser;
    
public:
    http_request() = default;
    http_request(const std::string &tmp):content(tmp), parser(std::make_shared<http_attribute>(http_attribute(content))){}
    
    void add_content(const std::string &tmp);
    http_request_code::state get_request_code();

};

void http_request::add_content(const std::string &tmp)
{
    
    content += tmp;
    parser->add_content(tmp);
}

http_request_code::state http_request::get_request_code()
{
    return parser->get_http_request_code();
}

};

#endif