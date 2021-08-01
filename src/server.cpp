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

void startGame();

int main() {
    httplib::Server svr;
    int numberOfPlayers = 4;
    int numberOfConnected = 0;
    bool  isGameStart = false;
    string players[numberOfPlayers];
    board = &Board::currentBoard;

    svr.Get("/new_game", [&](const httplib::Request &req, httplib::Response &res) {
        if (numberOfPlayers == numberOfConnected) {
            res.set_content("you can't join the game", "text/plain");
            return;
        }
        string id = playerIdGenerator(numberOfConnected);
        res.set_content(id + " waiting to start game ...", "text/plain");
        players[numberOfConnected] = id;
        numberOfConnected++;
        cout << id << " join to game" << endl;
        if (numberOfConnected == numberOfPlayers) {
            startGame();
            res.set_content(id + "game started", "text/plain");
        }
    });

    svr.Get("/update", [&](const httplib::Request &req, httplib::Response &res) {
        // send current board.
        if ('1' <= board->mat[5][5] && board->mat[5][5] <= '4') {
            cout << "Winner is: Player number " << board->mat[5][5] << endl;
            cout << "Game is end" << endl;
            numberOfConnected = 0;
            isGameStart = false;
        }
        board = &Board::currentBoard;
        string response = board->convertBoardToString();
        res.body = response;
        res.status = HTTP_200_OK;

    });
    svr.Post("/play", [&](const httplib::Request &req, httplib::Response &res) {
        string inputCommand = req.body;
        if (inputCommand[0] != (char)(turn%numberOfPlayers + '1')){
            res.body = "not_your_turn";
            return;
        }
        Command command(inputCommand);
        if (command.execute()) {
            res.body = "true";
        } else {
            res.body = "false";
            return;
        }
        res.status = HTTP_200_OK;
        turn++;
        turn = turn % numberOfPlayers;
    });

    svr.Post("/my_turn", [&](const httplib::Request &req, httplib::Response &res) {
        if (req.body[0] == to_string(turn+1)[0] && isGameStart){
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

void startGame() {
    turn = 0;
    cout << "Game is starting" << endl;
    board = &Board::currentBoard;
    board->setEmptyMap();
}
