#ifndef __HTTPPROJECT_HTTP_SERVER_H__
#define __HTTPPROJECT_HTTP_SERVER_H__

#include "http_conn.h"

namespace http_project
{

class http_server
{
public:
    std::shared_ptr<http_server> create(char* ip, char* port);
    ~http_server(){};
    void run();

private:
    http_server(const char* ip, const int port);
    void socket_();
    void bind_();
    void listen_();
    void set_epoll_event();
    void init();

public:
    static const int MAX_EVENT_NUM = INT32_MAX;
    static const int MAX_FD = 65536;


private:
    const char* m_ip;
    int m_port;
    int m_listenfd;
    int m_epollfd;
    epoll_event* m_events;
    std::unordered_map<int, std::shared_ptr<http_conn>>conntions;
    static std::shared_ptr<http_server>m_instance;

};



};



#endif