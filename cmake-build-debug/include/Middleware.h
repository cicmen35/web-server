#ifndef WEB_SERVER_MIDDLEWARE_H
#define WEB_SERVER_MIDDLEWARE_H

#include <string>

void logRequest(std::string& request);
void authenticateRequest(std::string& request);


#endif //WEB_SERVER_MIDDLEWARE_H
