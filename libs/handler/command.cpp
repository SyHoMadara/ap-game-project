#include "iostream"
#include "command.h"

string Command::commands[] = {"up","down","right","left"};
regex Command::wallRegex(R"(wall\((\d+),(\d+)\)((right)|(up)))");;

vector<string> split(std::string string, std::string reg);

Command::Command(string command) {
    this->command = command;
    this->is_valid = false;
}

void Command::validate() {
    for (string s : commands){
        if (s == command){
            is_valid = true;
            return;
        }
    }
    if (regex_match(command, wallRegex)){
        is_valid = true;
        return;
    }
}

string Command::getCommand(){
    return command;
}

bool Command::isValid() {
    return is_valid;
}

bool Command::execute() {
    if (!is_valid) return false;
    if (command == "up"){

    } else if (command == "down") {

    } else if (command == "right") {

    } else if (command == "left") {

    } else {  // is set wall command : wall(5,10)up or wall(5,10)left
        pair<int, int> location;
        int endInd = 0;
        for (int i = 5; i < command.size(); ++i) {
            if (command[i] == ')') {
                endInd = i - 1;
                break;
            }
        }
        auto number = split(command.substr(5,endInd), ",");
        location.first = std::stoi(number[0]);
        location.second = std::stoi(number[1]);
        // todo fill board.

    }
    return true;
}

vector<string> split(std::string string, std::string reg){
    regex e(reg);
    regex_token_iterator<string::iterator> i(string.begin(), string.end(), e, -1);
    regex_token_iterator<string::iterator> end;
    vector<std::string> list;
    while (i != end){
        list.push_back(*i);
        i++;
    }
    return list;
}
