#include "iostream"
#include "map.h"
#include <unordered_map>
#include <sstream>

Board Board::currentBoard(4);

Board::Board() {
    createBoard(4);
}

Board::Board(int numberOfPlayers) {
    this->numberOfPlayers = numberOfPlayers;
    createBoard(numberOfPlayers);
}

void Board::setEmptyMap() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (i == 5 & j == 5)
                mat[i][j] = 'O';
            else
                mat[i][j] = '-';
        }
    }

}

void Board::printMap() {
    printf(" ");
    for (int i = 0; i < 11; ++i) {
        printf(" %2d",i+1);
    }
    cout<<'\n';
    for (int i = 0; i < 11; i++) {
        printf("%2d",i+1);
        for (int j = 0; j < 11; j++) {
            cout << " " << mat[i][j] << ' ';
        }
        if (i != 10)
            cout << "\n";
    }
    cout<<'\n';
    return;
}

void Board::createBoard(int numberOfPlayers) {
    if (numberOfPlayers == 2) {
        int n = 11;
        mat = new char *[n];
        for (int i = 0; i < n; i++)
            mat[i] = new char[n];
        setEmptyMap();
        mat[0][0] = '1';
        mat[10][10] = '2';

    } else if (numberOfPlayers == 3) {
        int n = 11;
        mat = new char *[n];
        for (int i = 0; i < n; i++)
            mat[i] = new char[n];
        setEmptyMap();
        mat[0][0] = '1';
        mat[0][10] = '2';
        mat[10][0] = '3';

    } else if (numberOfPlayers == 4) {
        int n = 11;
        mat = new char *[n];
        for (int i = 0; i < n; i++)
            mat[i] = new char[n];
        setEmptyMap();
        mat[0][0] = '1';
        mat[10][10] = '4';
        mat[0][10] = '2';
        mat[10][0] = '3';

    } else {

    }
}

int *Board::findPlayer(char player) {
    int i = 0, j = 0;
    int *arr = new int[2];
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            if (mat[i][j] == player) {
                arr[0] = i;
                arr[1] = j;
                return arr;
            }
        }
    }
    return arr;
}

bool Board::validMove(char player, string move) {
    int *arr = NULL;
    arr = findPlayer(player);
    if (move == "up") {
        if (arr[0] == 0)
            return false;
        else if (mat[arr[0] - 1][arr[1]] != '-' && mat[arr[0] - 1][arr[1]] != 'O')
            return false;
    } else if (move == "down") {
        if (arr[0] == 10)
            return false;
        else if (mat[arr[0] + 1][arr[1]] != '-' && mat[arr[0] + 1][arr[1]] != 'O')
            return false;
    } else if (move == "left") {
        if (arr[1] == 0)
            return false;
        else if (mat[arr[0]][arr[1] - 1] != '-' && mat[arr[0]][arr[1] - 1] != 'O')
            return false;
    } else { // right
        if (arr[1] == 10)
            return false;
        else if (mat[arr[0]][arr[1] + 1] != '-' && mat[arr[0]][arr[1] + 1] != '-')
            return false;
    }
    return true;
}

//up
bool Board::moveUp( char player) {
    if (validMove( player, "up")) {
        int *arr = new int[2];
        arr = findPlayer(player);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0] - 1][arr[1]] = player;
        return true;
    } else {
        cerr << "you cant do this.";
        return false ;
    }
}

//down
bool Board::moveDown( char player) {
    if (validMove( player, "down")) {
        int *arr = new int[2];
        arr = findPlayer(player);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0] + 1][arr[1]] = player;
        return true;
    } else {
        cerr << "you cant do this.";
        return false ;
    }
}

//left
bool Board::moveLeft( char player) {
    if (validMove(player, "left")) {
        int *arr = new int[2];
        arr = findPlayer(player);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0]][arr[1] - 1] = player;
        return true;
    } else {
        cerr << "you cant do this.";
        return false ;
    }
}

//right
bool Board::moveRight( char player) {
    if (validMove( player, "right")) {
        int *arr = new int[2];
        arr = findPlayer(player);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0]][arr[1] + 1] = player;
        return true;
    } else {
        cerr << "you cant do this.";
        return false ;
    }
}

bool Board::validWall( char player, string move_like , int row , int column) {
    if (move_like == "up" || move_like == "down") {

        if (row == 0 || row== 10) {
            return false;
        } else if (mat[row][column] != '-' || mat[row+1][column] != '-' || mat[row-1][column] != '-') {
            return false;
        }
    } else if (move_like == "left" || move_like == "right") {
        if (column == 0 || column == 10) {
            return false;
        } else if (mat[row][column] != '-' || mat[row][column-1] != '-' || mat[row][column+1] != '-') {
            return false;
        }
    } else {
        cerr << "this move not exist";
        exit(1);
    }
    return true;
}

//wall
bool Board::wall( char player, string move_like,int row , int column) {

    if (move_like == "up" || move_like == "down") {
        if (validWall( player, move_like , row , column)) {
            mat[row][column] = 'w';
            mat[row+ 1][column] = 'w';
            mat[row - 1][column] = 'w';
            return true;
        } else {
            cerr << "you cant put a wall in this section";
            return false ;
        }
    } else {
        if (validWall( player, move_like,row , column)) {
            mat[row][ column] = 'w';
            mat[row][ column + 1] = 'w';
            mat[row][ column- 1] = 'w';
            return true;
        } else {
            cerr << "you cant put a wall in this section";
            return false;
        }
    }
}

string Board::convertBoardToString() {

    int NumberOfWall = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (mat[i][j] == 'w') {
                NumberOfWall++;
            }
        }

    }
    string responseWalls;
    string responsePlayer;
    responseWalls += to_string(NumberOfWall) + "\n";
    responsePlayer += to_string(numberOfPlayers) + "\n";

    int wallCounter = 0;
    char walls[NumberOfWall][2];
    char players[4][2];
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (mat[i][j] == 'w') {
                responseWalls += to_string(i) + " " + to_string(j) + "\n";
                wallCounter++;
            }
            if (mat[i][j] <= '4' && mat[i][j] >= '1'){
                string player;
                player += mat[i][j];
                responsePlayer += player + " " + to_string(i) + " " + to_string(j) + "\n";
            }

        }

    }
    return responseWalls + responsePlayer;


}

void Board::convertStringToBoard(const string& board) {
    stringstream cin(board);
    int wallNumber;
    int x,y;
    string clientNumber;
    cin >> wallNumber;
    for (int i = 0; i < wallNumber; ++i) {
        cin >> x >> y;
        mat[x][y] = 'w';
    }
    int m;
    string player;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> player >> x >> y;
        mat[x][y] = player[0];
    }

}