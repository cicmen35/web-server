#include "../include/WebServer.h"
#include "../include/ClientHandler.h"
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <sys/socket.h>

WebServer::WebServer(int port, int backlog)
        : port(port), backlog(backlog), server_fd(-1), running(false) {}

WebServer::~WebServer() {
    stop();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
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

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, backlog) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server initialized and listening on port " << port << std::endl;
}

void WebServer::acceptClients() {
    while (running) {
        int clientSocket;
        socklen_t addrlen = sizeof(address);
        clientSocket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (clientSocket < 0) {
            if (running) {
                perror("Accept failed");
            }
            continue;
        }

        // Launch a new thread to handle the client
        threads.emplace_back([clientSocket]() {
            ClientHandler handler(clientSocket);
            handler.processRequest();
        });
    }
}

void WebServer::run() {
    running = true;
    std::cout << "Server running. Waiting for connections..." << std::endl;
    acceptClients();
}

void WebServer::stop() {
    running = false;
    if (server_fd >= 0) {
        close(server_fd);
        server_fd = -1;
    }
    std::cout << "Server stopped." << std::endl;
}