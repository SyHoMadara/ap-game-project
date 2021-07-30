//
// Created by Hossein on 7/31/21.
//

#include <fstream>
#include "FileReader.h"
#include "iostream"

using namespace std;

string FileReader::convert_file_to_string(string address){
    char *str;
    fstream file;
    file.open(address, ios::in | ios::binary);
    file.read(str, sizeof(file));
    string stri(str);
    return stri;
}