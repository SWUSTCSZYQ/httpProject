#ifndef __HTTPPROJECT_UTILS_OUTPUTUTILS_H__
#define __HTTPPROJECT_UTILS_OUTPUTUTILS_H__


namespace http_project
{

void show_error(int connfd, const char* info)
{
    printf("%s", info);
    std::cout << info << std::endl;
    send(connfd, info, strlen(info), 0);
    close(connfd);

}

};

#endif