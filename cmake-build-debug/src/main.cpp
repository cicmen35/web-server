#include <iostream>
#include "../include/WebServer.h"

int main(){
    WebServer server(8080, 10);
    server.init();
    server.run();
    return 0;
}
