#include <iostream>
#include "../include/WebServer.h"

int main(){
    // Create a WebServer instance
    WebServer server(8080);

    // Initialize the server
    server.init();

    // Run the server to accept and handle connections
    server.run();
    return 0;
}
