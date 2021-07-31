#include <iostream>
#include "../libs/httplib.h"

using namespace std;

void startGame(string username, httplib::Client &cli);
string play(httplib::Client &cli, string command);
string update(httplib::Client &cli, string username);

int main() {
    httplib::Client cli("127.0.0.1:8000");
    //first time request for getting username and join the game.
    auto requestToPlay = cli.Get("/new_game");
    string username;
    if(requestToPlay){
        username = requestToPlay->body;
        cout << "your id: " << username << endl;
        if(username.at(0) == '/'){ // username[0]
            cout << "true" << endl;
            cout << "waiting to start game" << endl;
            startGame(username, cli);
        }
    }
    else{
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

void startGame(string username, httplib::Client &cli){
    string isMyTurn = username.append("_turn");
    while(true){
        //update board
        string updatedBoard = update(cli, username);
        auto myTurn = cli.Get(isMyTurn.c_str());
        if(myTurn->body == isMyTurn){
            // play and get result
            string resultOfPlay;
            do{
                resultOfPlay = play(cli, username);
                if (resultOfPlay == "true"){
                    cout << "your move done!" << endl;
                }
                else if(resultOfPlay == "false"){
                    cout << "foul move" << endl;
                }
            } while (resultOfPlay != "true");
        }
        if(myTurn->body == "end"){
            cout << "Game is end" << endl;
            break;
        }
    }
}

string play(httplib::Client &cli, string username){
    string play = username.append("_play");
    cout << "Enter your move: ";
    string command;
    cin >> command;
    auto resultOfPlay = cli.Post(play.c_str(), command, "text/plain");
    return resultOfPlay->body;
}

string update(httplib::Client &cli, string username){
    string update = username.append("_update");
    auto updatedBoard = cli.Get(update.c_str());
    return updatedBoard->body;
}

