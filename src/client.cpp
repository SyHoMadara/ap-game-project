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
    for (int i = 0; i < 1e9; ++i);
    while (true) {
        //update board
        update(cli, username);
        // play and get result
        while (cli.Post("/my_turn", playerNumber, "text/plain")->body != "true");
        string resultOfPlay;
        do {
            resultOfPlay = play(cli, username);
            if (resultOfPlay == "true") {
                cout << "your move done!" << endl;
            } else if (resultOfPlay == "false") {
                cout << "foul move" << endl;
            }
        } while (resultOfPlay != "true");
        if (currentBoard.mat[5][5] <= '4' && currentBoard.mat[5][5] >= '1') {
            cout << "game hase been ended" << endl;
            break;
        }
        system("clear");
    }
    if (currentBoard.mat[5][5] == playerNumber[0]) {
        cout << "you are winner" << endl;
    } else {
        cout << "you loosing game" << endl;
    }
}

string chooseCommand() {
    cout << "1.move up" << endl;
    cout << "2.move down" << endl;
    cout << "3.move right" << endl;
    cout << "4.move left" << endl;
    cout << "5.put wall" << endl;
    int chosenNumb;
    string s;
    cout << "your command : ";
    cin >> chosenNumb;
    switch (chosenNumb) {
        case 1:
            return "up";
        case 2:
            return "down";
        case 3:
            return "right";
        case 4:
            return "left";
        case 5:
            cout << "enter location as format (8,10)up or down\n    ";
            cin >> s;
            return "wall" + s;
        default :
            return "false";
    }

}

string play(httplib::Client &cli, string username) {
    string command = playerNumber + '\n';
    command += chooseCommand();
    auto resultOfPlay = cli.Post("/play", command, "text/plain");
    return resultOfPlay->body;
}

void update(httplib::Client &cli, string username) {
    string update = username.append("_update");
    auto res = cli.Get("/update");

    currentBoard.convertStringToBoard(res->body);
    system("clear");
    currentBoard.printMap();
}

