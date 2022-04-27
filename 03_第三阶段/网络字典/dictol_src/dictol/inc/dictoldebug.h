#ifndef DICTOL_DEBUG_H
#define DICTOL_DEBUG_H

//仅客户端使用
#define DICTOL_CLIENT_DEBUG_ERROR
#define DICTOL_CLIENT_DEBUG_WARNING
#define DICTOL_CLIENT_DEBUG_INFO

#ifdef DICTOL_CLIENT_DEBUG_ERROR
#define PrintClientError printf("<Client Error>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintClientError(...)
#endif
//PrintClientError(...) C99才支持
//用法PrintClientError同printf,注意不可使用在不加{}的条件体和循环体,以下雷同

#ifdef DICTOL_CLIENT_DEBUG_WARNING
#define PrintClientWarning printf("<Client Warning>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintClientWarning(...)
#endif

#ifdef DICTOL_CLIENT_DEBUG_INFO
#define PrintClientInfo printf("<Client Info>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintClientInfo(...)
#endif


//仅服务器使用
#define DICTOL_SERVER_DEBUG_ERROR
#define DICTOL_SERVER_DEBUG_WARNING
#define DICTOL_SERVER_DEBUG_INFO

#ifdef DICTOL_SERVER_DEBUG_ERROR
#define PrintServerError printf("<Server Error>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintServerError(...)
#endif

#ifdef DICTOL_SERVER_DEBUG_WARNING
#define PrintServerWarning printf("<Server Warning>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintServerWarning(...)
#endif

#ifdef DICTOL_SERVER_DEBUG_INFO
#define PrintServerInfo printf("<Server Info>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintServerInfo(...)
#endif

//仅公共库代码使用
#define DICTOL_PUBLIC_DEBUG_ERROR
#define DICTOL_PUBLIC_DEBUG_WARNING
#define DICTOL_PUBLIC_DEBUG_INFO

#ifdef DICTOL_PUBLIC_DEBUG_ERROR
#define PrintPublicError printf("<Public Error>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintPublicError(...)
#endif

#ifdef DICTOL_PUBLIC_DEBUG_WARNING
#define PrintPublicWarning printf("<Public Warning>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintPublicWarning(...)
#endif

#ifdef DICTOL_PUBLIC_DEBUG_INFO
#define PrintPublicInfo printf("<Public Info>at %s:%d--",__FILE__,__LINE__);printf
#else
#define PrintPublicInfo(...)
#endif


#endif
