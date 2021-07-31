#include <iostream>
#include "../libs/httplib.h"

using namespace std;


int main() {
    httplib::Client client("127.0.0.1:8000");
    auto res = client.Get("/hi");
    if (res->status == HTTP_200_OK){
        cout << res->body << "status : " << res->status << '\n';
    } else {
        cout << res.error();
    }

    return 0;

}
