#ifndef __HTTPPROJCET_HTTP_CONN_CPP__
#define __HTTPPROJCET_HTTP_CONN_CPP__

#include "http_conn.h"

namespace http_project
{

int http_conn::m_epolled = -1;
int http_conn::m_user_count = 0;


void http_conn::close_conn(bool real_close)
{
    if(real_close and m_sockfd != -1)
    {
        removefd(m_epolled, m_sockfd);
        m_sockfd = -1;
        --m_user_count;
    }
}


http_conn::http_conn(int sockfd, sockaddr_in& address)
:buffer(""), m_sockfd(sockfd), m_address(address)
{
    m_request = std::make_shared<http_request>(http_request(buffer));
}

void http_conn::init()
{
    int reuse = 1;
    setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)); // for debug
    addfd(m_epolled, m_sockfd, true);
    ++m_user_count;
}

bool http_conn::read()
{
    int byte_read = 0;
    while(true)
    {
        char m_read[MAX_READ_SIZE];
        byte_read = recv(m_sockfd, m_read, MAX_READ_SIZE, 0);
        if(byte_read == -1)
        {
            if(errno == EAGAIN or errno == EWOULDBLOCK)
                break;
            return false;
        }
        else if(byte_read == 0)
            return false;
        buffer += std::string(m_read, byte_read);

    }
    return true;
}

bool http_conn::write()
{
    
}


};



#endif