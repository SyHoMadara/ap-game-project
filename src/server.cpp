#include <iostream>
#include "../libs/httplib.h"

using namespace std;

const char *const domain = "http://127.0.0.1";
const string port_str = "8000";
const long long port = 8000;

// status
#ifndef HTTP_404_NOT_FOUND
#define HTTP_404_NOT_FOUND 404
#define HTTP_200_OK 200
#define HTTP_403_FORBIDDEN 403;
#define HTTP_403_METHOD_NOT_ALLOWED 405;
#endif

int main() {
    httplib::Server server;

    // request and response.
    server.Get("/hi", [](const httplib::Request &request, httplib::Response response) {
        cout << "get method with /hi" << '\n';
        response.set_content("Get method accepted", "text/plain");
        response.status = HTTP_404_NOT_FOUND;
    });


    server.listen(domain, port);

}
