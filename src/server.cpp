#include <iostream>
#include "../libs/httplib.h"
#include "handler/FileReader.h"
#include "../libs/map.h"
#include "../libs/handler/command.h"

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
Board *board;
int turn = 0;

string playerIdGenerator(int numberOfConnected);

void startGame(bool isGameStart, int numberOfPlayers, string players[], httplib::Server &svr);

int main() {
    httplib::Server svr;
    int numberOfPlayers = 4;
    int numberOfConnected = 0;
    bool isGameStart = false;
    string players[numberOfPlayers];

    svr.Get("/new_game", [&](const httplib::Request &req, httplib::Response &res) {
        if (numberOfPlayers == numberOfConnected) {
            res.set_content("you can't join the game", "text/plain");
            res.status = HTTP_403_FORBIDDEN;
            return;
        }
        string id = playerIdGenerator(numberOfConnected);
        res.set_content(id + " waiting to start game ...", "text/plain");
        players[numberOfConnected] = id;
        numberOfConnected++;
        cout << id << " join to game" << endl;
        if (numberOfConnected == numberOfPlayers) {
            startGame(true, numberOfPlayers, players, svr);
            res.set_content(id + "game started", "text/plain");
        }
    });

    svr.Get("/update", [&](const httplib::Request &req, httplib::Response &res) {
        // send current board.
        if ('1' <= board->mat[5][5] && board->mat[5][5] <= '4') {
            cout << "Winner is: Player number " << board->mat[5][5] << endl;
            cout << "Game is end" << endl;
            isGameStart = false;
        }
        string response = board->convertBoardToString();
        res.body = response;
        res.status = HTTP_200_OK;

    });
    cout << "Player " << turn % numberOfPlayers + 1 << "is your turn." << endl;
    svr.Post("/play", [&](const httplib::Request &req, httplib::Response &res) {
        string inputCommand = req.body;
        if (inputCommand[0] != (char)(turn%numberOfPlayers + '0')){
            res.body = "not_your_turn";
            return;
        }
        Command command(inputCommand, turn % numberOfPlayers);
        if (command.execute()) {
            res.body = "true";
        } else {
            res.body = "false";
        }
        res.status = HTTP_200_OK;
        turn++;
        turn = turn % numberOfPlayers;
    });

    svr.Post("/my_turn", [&](const httplib::Request &req, httplib::Response &res) {
        if (req.body[0] == turn){
            res.body = "true";
        } else {
            res.body = "false";
        }
    });


    svr.listen(domain, port);
    cout << "server stopped" << endl;

}

string playerIdGenerator(int numberOfConnected) {
    string pl = "/pl";
    string id = std::to_string(numberOfConnected + 1);
    return pl.append(id);
}

void startGame(httplib::Server &svr) {
    turn = 0;
    cout << "Game is starting" << endl;
    board = &Board::currentBoard;
    board->setEmptyMap();

}
