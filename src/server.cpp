#include <iostream>
#include "../libs/httplib.h"
#include "handler/FileReader.h"

using namespace std;

// status

#ifndef HTTP_404_NOT_FOUND
#define HTTP_404_NOT_FOUND 404
#define HTTP_200_OK 200
#define HTTP_403_FORBIDDEN 403;
#define HTTP_403_METHOD_NOT_ALLOWED 405;
#endif

const char *const domain = "127.0.0.1";
const string port_str = "8000";
const long long port = 8000;

string playerIdGenerator(int numberOfConnected);

void startGame(bool isGameStart, int numberOfPlayers, string players[numberOfPlayers], httplib::Server &svr);

int main() {
    httplib::Server server;
    int numberOfPlayers = 4;
    int numberOfConnected = 0;
    bool isGameStart = false;
    string players[numberOfPlayers];

    server.Post("/pl", [&](const httplib::Request &req, httplib::Response &res) {
        cout << req.body << endl;
    });


    server.Get("/update", [](const httplib::Request &req, httplib::Response &res) {

    });

    server.Get("/new_game", [&](const httplib::Request &req, httplib::Response &res) {
        if (numberOfPlayers == numberOfConnected) {
            res.set_content("you can't join the game", "text/plain");
            res.status = HTTP_403_FORBIDDEN;
            return;
        }
        string id = playerIdGenerator(numberOfConnected);
        res.set_content(id, "text/plain");
        players[numberOfConnected] = id;
        numberOfConnected++;
        if (numberOfConnected == numberOfPlayers) {
            startGame(true, numberOfPlayers, players, server);
        }
    });


    server.listen(domain, port);
    cout << "server stopped" << endl;

}

string playerIdGenerator(int numberOfConnected) {
    string pl = "/pl";
    string id = std::to_string(numberOfConnected + 1);
    return pl.append(id);
}

void startGame(bool isGameStart, int numberOfPlayers, string players[numberOfPlayers], httplib::Server &svr) {
    int turn = 0;
    if (isGameStart) {
        cout << "Game is starting" << endl;
    }
    while (isGameStart) {
        string player = players[turn % numberOfPlayers];
        string update = player + "_update";
        string play = player + "_play";
        string turnCommand = player + "_turn";
        svr.Get(turnCommand, [&](const httplib::Request &req, httplib::Response &res) {
            res.set_content(turnCommand, "text/plain");

        });
        svr.Get(update, [&](const httplib::Request &req, httplib::Response &res) {
            // send current board.
        });
        cout << "Player " << turn % numberOfPlayers + 1 << "is your turn." << endl;
        svr.Post(play, [&](const httplib::Request &req, httplib::Response &res) {
            string command = req.body;
            //cout << players[turn % numberOfPlayers] << " command is: " << command << endl;
            //get command from client and use it to play
            turn++;
            res.set_content(R"({"request" = "successful"})", "text.plain");
        });

        if (/*game end condition*/ false) {
            cout << "Winner is: ";
            cout << "Game is end" << endl;
            svr.stop();
            break;
        }
        svr.listen("127.0.0.1", 8000);
    }
}