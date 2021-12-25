#ifndef __HTTPPROJECT_HTTP_SERVER_CPP__
#define __HTTPPROJECT_HTTP_SERVER_CPP__


#include "http_server.h"
#include "utils/output_utils.h"

namespace http_project
{

const int http_server::MAX_EVENT_NUM;
const int http_server::MAX_FD;

std::shared_ptr<http_server> http_server::m_instance = nullptr;

std::shared_ptr<http_server> http_server::create(char* ip, char* port)
{

    if(!m_instance)
    {

        m_instance = std::make_shared<http_server>(http_server(ip, atoi(port)));

    }
    return m_instance;
}

http_server::http_server(const char* ip, const int port)
:m_ip(ip), m_port(port), m_epollfd(-1), m_listenfd(-1)
{}

void http_server::init()
{
    socket_();
    bind_();
    listen_();
    set_epoll_event();
}

void http_server::run()
{
    init();
    while(true)
    {
        int number = epoll_wait(m_epollfd, m_events, MAX_EVENT_NUM, -1);
        if(number < 0 and errno != EINTR)
        {
            std::cout << "epoll failure" << std::endl;
            break;
        }

        for(int i = 0; i < number; ++i)
        {
            int sockfd = m_events[i].data.fd;
            if(sockfd == m_listenfd) 
            {
                // a new connection
                struct sockaddr_in client_address;
                socklen_t addr_len = sizeof(client_address);
                int connfd = accept(m_listenfd, (struct sockaddr*)&client_address, &addr_len);
                if(connfd < 0)
                {
                    std::cout << "errrno is : " << errno << std::endl;
                    continue;
                }
                if(http_conn::m_user_count > MAX_FD)
                {
                    show_error(connfd, "internal server busy");
                    continue;
                }
                std::shared_ptr<http_conn>conn(new http_conn(connfd, client_address));
                conntions[connfd] = conn;

            }
            else if(m_events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                conntions.erase(sockfd);
                std::cout << "一个连接已经断开!" << std::endl;
                /*
                epollrdhub: client closed or the write operation of client closed
                epollhub: hang up
                epollerr: error
                */
            }
            else if(m_events[i].events & EPOLLIN)
            {
                //epollin: There is data to read
                
            }
            else if(m_events[i].events & EPOLLOUT)
            {
                //epollout: There is data to write
            }
            else continue;
        }
    }
}

void http_server::socket_()
{
    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);
}

void http_server::bind_()
{
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, m_ip, &address.sin_addr);
    address.sin_port = htons(m_port);

    int ret = bind(m_listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret >= 0);
}

void http_server::listen_()
{
    int ret = listen(m_listenfd, 5);
    assert(ret >= 0);
}


void http_server::set_epoll_event()
{
    m_epollfd = epoll_create(5);
    assert(m_epollfd != -1);
    addfd(m_epollfd, m_listenfd, false);
}

};


#endif