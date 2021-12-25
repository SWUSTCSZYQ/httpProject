#ifndef __HTTPPROJECT_HTTP_CONN_H__
#define __HTTPPROJECT_HTTP_CONN_H__


#include "utils/fd_set_utils.h"
#include "http_request.h"

namespace http_project{

class http_conn
{
private:
    
public:
    http_conn(int sockfd, sockaddr_in& address);
    ~http_conn();
    void init();
    void close_conn(bool real_close = true);
    void process();
    bool read();
    bool write();

public:
    static const int MAX_READ_SIZE = 4096;
    static int m_epolled;
    static int m_user_count;

private:
    int m_sockfd;
    sockaddr_in m_address;
    std::string buffer;
    std::unordered_map<std::string, std::string>http_attribute;
    std::shared_ptr<http_request>m_request;
};


};


#endif