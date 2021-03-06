#include "iostream"
#include "command.h"
#include "map.h"

string Command::commands[] = {"up","down","right","left"};
regex Command::wallRegex(R"(wall\((\d+),(\d+)\)((right)|(up)))");;

vector<string> split(std::string string, std::string reg);

Command::Command(string command) {
    this->command = command;
    this->is_valid = false;
}

void Command::validate() {
    stringstream ss(command);
    ss >> playerNumber;
    string s;
    ss >> s;
    command = s;
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
    validate();
    if (!is_valid) return false;
    // you can access to current board by Board::currentBoard
    Board *board = &Board::currentBoard;
    if (command == "up"){
       return board->moveUp(playerNumber) ;

    } else if (command == "down") {
       return board->moveDown(playerNumber);

    } else if (command == "right") {
       return board->moveRight(playerNumber) ;

    } else if (command == "left") {
       return board->moveLeft(playerNumber) ;

    } else {  // is set wall command : wall(5,10)up or wall(5,10)left
        pair<int, int> location;
        bool is_up = false;
        int endInd = 0;
        for (int i = 5; i < command.size(); ++i) {
            if (command[i] == ')') {
                endInd = i - 1;
                break;
            }
        }
        if (command[endInd+2]== 'u'){
            is_up = true;
        }
        auto number = split(command.substr(5,endInd), ",");
        location.first = std::stoi(number[0]);
        location.second = std::stoi(number[1]);
        location.first--;
        location.second--;
        if(is_up){
            return board->wall(playerNumber,"up",location.first, location.second);
        } else {
            return board->wall(playerNumber,"left",location.first, location.second) ;
        }


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
