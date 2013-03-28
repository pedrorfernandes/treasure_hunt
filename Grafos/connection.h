#ifndef _CONNECTION_
#define _CONNECTION_

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef WIN32
#define WINDOWS
#elif WIN64
#define WINDOWS
#endif

#ifdef WINDOWS
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#endif

#include <string>
#include <iostream>

using namespace std;

class Connection {
public:
    Connection(int port);
    
    bool sendMsg(string msg);
    string readLine();
private:
#ifndef WINDOWS
    int sock;
#else
    SOCKET sock;
#endif
};

#endif
