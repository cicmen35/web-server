#ifndef WEB_SERVER_WEBSERVER_H
#define WEB_SERVER_WEBSERVER_H

#include <netinet/in.h>
#include <string>
#include <functional>
#include <vector>

class WebServer {
private:
    int server_fd;                // Server socket file descriptor
    struct sockaddr_in address;   // Server address structure
    int port;                     // Port number
    int backlog;                  // Maximum pending connections
    std::atomic<bool> running;    // Flag to indicate whether the server is running
    std::vector<std::function<void(std::string&)>> middlewares; // Middleware functions
    void handleRequest(int clientSocket);

public:
    WebServer(int port, int backlog = 3);   // Constructor
    ~WebServer();                           // Destructor
    void init();                            // Initialize the server (create, bind, and listen)
    void run();                             // Run the server to accept and handle client connections
    void stop();                            // Stop the server
};

#endif //WEB_SERVER_WEBSERVER_H