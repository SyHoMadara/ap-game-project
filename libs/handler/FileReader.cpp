#include <fstream>
#include "iostream"
#include "FileReader.h"


string FileReader::convert_file_to_string(string address){
    char *str;
    fstream file;
    file.open(address, ios::in | ios::binary);
    file.read(str, sizeof(file));
    string stri(str);
    return stri;
}