#include "WebServer.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

WebServer::WebServer(int port, int backlog) : port(port), backlog(backlog), server_fd(-1) {
    memset(&address, 0, sizeof(address));
}

WebServer::~WebServer() {
    if (server_fd >= 0) {
        close(server_fd);
        std::cout << "Server socket closed." << std::endl;
    }
}

void WebServer::init() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket created successfully." << std::endl;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket bound to port " << port << std::endl;

    if (listen(server_fd, backlog) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server is listening on port " << port << std::endl;
}

void WebServer::run() {
    int new_socket;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    std::cout << "Waiting for a connection..." << std::endl;

    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Connection accepted." << std::endl;

    read(new_socket, buffer, sizeof(buffer));
    std::cout << "Request received:\n" << buffer << std::endl;

    const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, World!";
    send(new_socket, response, strlen(response), 0);
    std::cout << "Response sent." << std::endl;

    close(new_socket);
    std::cout << "Connection closed." << std::endl;
}