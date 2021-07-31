#include <iostream>
#include <regex>
#include<string.h>
using namespace std;


#ifndef AP_PROJECT_GAME_COMMAND_H
#define AP_PROJECT_GAME_COMMAND_H

class Command {
private:
    string command;
    bool is_valid;
public:

    static string commands[];
    static regex wallRegex;

    string getCommand();
    bool isValid();

    explicit Command(string command);
    void validate();
    bool execute();

} ;

#endif //AP_PROJECT_GAME_COMMAND_H


