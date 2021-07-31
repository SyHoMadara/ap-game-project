#include <iostream>
#include <regex>
#include<string.h>
using namespace std;


#ifndef AP_PROJECT_GAME_COMMAND_H
#define AP_PROJECT_GAME_COMMAND_H

#endif //AP_PROJECT_GAME_COMMAND_H


class Command {
private:
    string command;
public:
    static const string commands[];
    static const regex wallRegex("wall\\((\\d+),(\\d+)\\)((down)|(up))");

    Command(string command);
    static bool validate(string command);
    static bool e;
} ;

Command::commands = {"up","down","right","left"};

Command::Command(string command) {
    this->command = command;
}

bool Command::validate(string command) {
    bool is_valid = false;
    for (string s : commands){
        if (s == command){
            is_valid = true;
            return is_valid;
        }
    }
    if (regex_match(command, wallRegex)){
        is_valid = true;
    }
    return is_valid;
}


