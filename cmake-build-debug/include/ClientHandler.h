#ifndef WEB_SERVER_CLIENTHANDLER_H
#define WEB_SERVER_CLIENTHANDLER_H

#include <string>

class ClientHandler {
private:
    int clientSocket;             // Socket for this client

public:
    explicit ClientHandler(int clientSocket);
    ~ClientHandler();

    void processRequest();        // Handle the client's request
};

#endif //WEB_SERVER_CLIENTHANDLER_H
