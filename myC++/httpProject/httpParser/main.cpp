#ifndef __HTTPPROJECT_MAIN_CPP__
#define __HTTPPROJECT_MAIN_CPP__

#include<memory>
#include<string>
#include<iostream>
#include "http_request.h"
using namespace http_project;

int main(int argc, char* argv[])
{
    std::shared_ptr<http_request>request = std::make_shared<http_request>(http_request(std::string("GET /chapter17/user.html HTTP/1.1\r\nAccept: image\r\nAccept-Language: zh-CN")));
    request->add_content(std::string("\r\n\r\n"));
    std::cout << request->get_request_code() << std::endl;
    return 0;
}


#endif