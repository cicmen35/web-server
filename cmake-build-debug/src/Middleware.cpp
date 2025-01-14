#include "../include/Middleware.h"
#include <iostream>

void logRequest(std::string& request) {
    std::cout << "Logging request: " << request << std::endl;
}

void authenticateRequest(std::string& request) {
    if (request.find("Authorization") == std::string::npos) {
        std::cout << "Request unauthorized" << std::endl;
    } else {
        std::cout << "Request authorized" << std::endl;
    }
}