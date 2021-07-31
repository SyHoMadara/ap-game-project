#include <iostream>
#include "../libs/httplib.h"
#include "../libs/map.h"

using namespace std;

void startGame(string username, httplib::Client &cli);

string play(httplib::Client &cli, string command);

void update(httplib::Client &cli, string username);

Board currentBoard(4);
string playerNumber;

int main() {
    httplib::Client cli("127.0.0.1:8000");
    //first time request for getting username and join the game.
    auto requestToPlay = cli.Get("/new_game");
    string username;
    if (requestToPlay) {
        username = requestToPlay->body;
        cout << "your id: " << username << endl;
        if (username.at(0) == '/') { // username[0]
            cout << "true" << endl;
            cout << "waiting to start game" << endl;
            playerNumber += username[3];
            startGame(username, cli);
        }
    } else {
        cout << "Server not response! the game is full." << endl;
        cout << requestToPlay->status;
        return 0;
    }

    cli.set_keep_alive(true);
    // send play command with username to play and get result of command
    string command; // set this command with your desired value
    // auto resultOfPlay = cli.Post(username.c_str(), command, "text/plain");


    //cout << cli.Get("/stop")->body << endl;

    return 0;

}

void startGame(string username, httplib::Client &cli) {
    while (true) {
        //update board
        update(cli, username);
        if (cli.Post("/my_turn", playerNumber, "text/plain")->body == "true"){
            // play and get result
            string resultOfPlay;
            do {
                resultOfPlay = play(cli, username);
                if (resultOfPlay == "true") {
                    cout << "your move done!" << endl;
                } else if (resultOfPlay == "false") {
                    cout << "foul move" << endl;
                }
            } while (resultOfPlay != "true");
        }
        if (currentBoard.mat[5][5] <= '4' && currentBoard.mat[5][5]>='1'){
            cout << "game hase been ended" << endl;
            break;
        }
    }
    if (currentBoard.mat[5][5] == playerNumber[0]){
        cout << "you are winner" << endl;
    } else {
        cout << "you loosing game" << endl;
    }
}

string play(httplib::Client &cli, string username) {
    string play = username.append("_play");
    cout << "Enter your move: ";
    string command =;
    cin >> command;
    auto resultOfPlay = cli.Post(play.c_str(), command, "text/plain");
    return resultOfPlay->body;
}

void update(httplib::Client &cli, string username) {
    string update = username.append("_update");
    auto res = cli.Get(update.c_str());
    do {
        res = cli.Get(update.c_str());
    } while (res->status != HTTP_200_OK);
    currentBoard.convertStringToBoard(res->body);
    system("clear");
    currentBoard.print_board();
}

