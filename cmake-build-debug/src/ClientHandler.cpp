#include "../include/ClientHandler.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

ClientHandler::ClientHandler(int clientSocket) : clientSocket(clientSocket) {}

ClientHandler::~ClientHandler() {
    if (clientSocket >= 0) {
        close(clientSocket);
        std::cout << "Client connection closed." << std::endl;
    }
}

void ClientHandler::processRequest() {
    char buffer[1024] = {0};
    read(clientSocket, buffer, sizeof(buffer));

    std::string request(buffer);
    std::cout << "Request received:\n" << request << std::endl;

    const char* response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, World!";
    send(clientSocket, response, strlen(response), 0);
}