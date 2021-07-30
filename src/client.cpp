#include <iostream>
#include "../libs/httplib.h"

using namespace std;


int main() {
    httplib::Client client("http://127.0.0.1:8000");
    auto res = client.Get("/hi");
    cout << res->body << "status : " << res->status << '\n';

    return 0;

}
