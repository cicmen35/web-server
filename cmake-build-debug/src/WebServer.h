#ifndef WEB_SERVER_WEBSERVER_H
#define WEB_SERVER_WEBSERVER_H

#include <netinet/in.h>

class WebServer {
private:
    int server_fd;                // Server socket file descriptor
    struct sockaddr_in address;   // Server address structure
    int port;                     // Port number
    int backlog;                  // Maximum pending connections

public:
    WebServer(int port, int backlog = 3);   // Constructor
    ~WebServer();                           // Destructor
    void init();                            // Initialize the server (create, bind, and listen)
    void run();                             // Run the server to accept and handle client connections
};

#endif //WEB_SERVER_WEBSERVER_H