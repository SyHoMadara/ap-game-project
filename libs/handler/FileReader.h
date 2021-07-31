#include <iostream>
using namespace std;

#ifndef AP_PROJECT_GAME_FILE_READER_H
#define AP_PROJECT_GAME_FILE_READER_H


class FileReader {
public:
    static std::string convert_file_to_string(std::string address);
};

string FileReader::convert_file_to_string(string address){
    char *str;
    fstream file;
    file.open(address, ios::in | ios::binary);
    file.read(str, sizeof(file));
    string stri(str);
    return stri;
}

#endif //AP_PROJECT_GAME_FILE_READER_H
