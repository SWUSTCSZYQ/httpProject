#ifndef __HTTPPROJECT_HTTP_REQUEST_CODE_H__
#define __HTTPPROJECT_HTTP_REQUEST_CODE_H__



namespace http_project{

class http_request_code{

public:

    enum http_code{
        NO_REQUEST = 0, GET_REQUEST,
        BAD_REQUEST, NO_RESOURCE,
        FORBIDDEN_RESOURCE,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };

    enum method{
        GET = 0, HEAD,
        POST, PUT,
        DELETE, TRACE,
        OPTIONS, CONNECT,
        PATCH
    };

    enum state{
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_REQUESTHEAD,
        CHECK_STATE_REQUESTCONTENT,
        CHECK_STATE_FINISH
    };


    enum parser_code
    {
        PARSER_ERROR = 0,
        PARSER_ING,
        PARSER_SUCCESS
    };
};

};

#endif