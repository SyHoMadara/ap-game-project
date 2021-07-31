#include <iostream>
#include <string>
#include <map>


using namespace std;

class Board {
private:
    int num_of_players;
    char **mat;

public:
    Board(int num_of_players);

    char **create_board(int num_of_players);

    char **set_empty(char **mat);

    void print_board(char **mat);

    int *find_player(char player, char **mat);

    bool valid_move(char **mat, char player, string move);

    char **move_up(char **mat, char player);

    char **move_down(char **mat, char player);

    char **move_left(char **mat, char player);

    char **move_right(char **mat, char player);

    bool valid_wall(char **mat, char player, string move_like);

    char **wall(char **mat, char player, string move_like);

    string JsonConvertToBoard();
};

Board::Board(int num_of_players) {
    this->num_of_players = num_of_players;
}

char **Board::set_empty(char **mat) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (i == 5 & j == 5)
                mat[i][j] = 'g';
            else
                mat[i][j] = '-';
        }
    }
    return mat;
}

void Board::print_board(char **mat) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            cout << mat[i][j] << ' ';
        }
        if (i != 10)
            cout << endl;
    }
    return;
}

char **Board::create_board(int num_of_players) {
    if (num_of_players == 2) {
        int n = 11;
        char **mat = new char *[n];
        for (int i = 0; i < n; i++)
            mat[i] = new char[n];
        set_empty(mat);
        mat[0][0] = '1';
        mat[10][10] = '2';
        print_board(mat);
        return mat;
    } else if (num_of_players == 3) {
        int n = 11;
        char **mat = new char *[n];
        for (int i = 0; i < n; i++)
            mat[i] = new char[n];
        set_empty(mat);
        mat[0][0] = '1';
        mat[0][10] = '2';
        mat[10][0] = '3';
        print_board(mat);
        return mat;
    } else if (num_of_players == 4) {
        int n = 11;
        char **mat = new char *[n];
        for (int i = 0; i < n; i++)
            mat[i] = new char[n];
        set_empty(mat);
        mat[0][0] = '1';
        mat[10][10] = '4';
        mat[0][10] = '2';
        mat[10][0] = '3';
        print_board(mat);
        return mat;
    } else {
        return 0;
    }
}

int *Board::find_player(char player, char **mat) {
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

bool Board::valid_move(char **mat, char player, string move) {
    int *arr = new int[2];
    arr = find_player(player, mat);
    if (move == "up") {
        if (arr[0] == 0)
            return false;
        else if (mat[arr[0] + 1][arr[1]] != '-')
            return false;
    } else if (move == "down") {
        if (arr[0] == 10)
            return false;
        else if (mat[arr[0] - 1][arr[1]] != '-')
            return false;
    } else if (move == "left") {
        if (arr[1] == 0)
            return false;
        else if (mat[arr[0]][arr[1] - 1] != '-')
            return false;
    } else //right
    {
        if (arr[1] == 10)
            return false;
        else if (mat[arr[0]][arr[1] + 1] != '-')
            return false;
    }
    return true;
}

//up
char **Board::move_up(char **mat, char player) {
    if (valid_move(mat, player, "up")) {
        int *arr = new int[2];
        arr = find_player(player, mat);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0] + 1][arr[1]] = player;
        return mat;
    } else {
        cerr << "you cant do this.";
        exit(1);
    }
}

//down
char **Board::move_down(char **mat, char player) {
    if (valid_move(mat, player, "down")) {
        int *arr = new int[2];
        arr = find_player(player, mat);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0] - 1][arr[1]] = player;
        return mat;
    } else {
        cerr << "you cant do this.";
        exit(1);
    }
}

//left
char **Board::move_left(char **mat, char player) {
    if (valid_move(mat, player, "left")) {
        int *arr = new int[2];
        arr = find_player(player, mat);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0]][arr[1] - 1] = player;
        return mat;
    } else {
        cerr << "you cant do this.";
        exit(1);
    }
}

//right
char **Board::move_right(char **mat, char player) {
    if (valid_move(mat, player, "right")) {
        int *arr = new int[2];
        arr = find_player(player, mat);
        mat[arr[0]][arr[1]] = '-';
        mat[arr[0]][arr[1] + 1] = player;
        return mat;
    } else {
        cerr << "you cant do this.";
        exit(1);
    }
}

bool Board::valid_wall(char **mat, char player, string move_like) {
    if (move_like == "up" || move_like == "down") {
        int *arr = new int[2];
        arr = find_player(player, mat);
        if (arr[0] == 0 || arr[0] == 10) {
            return false;
        } else if (mat[arr[0] - 1][arr[1]] != '-' || mat[arr[0] + 1][arr[1]] != '-') {
            return false;
        }
    } else if (move_like == "left" || move_like == "right") {
        int *arr = new int[2];
        arr = find_player(player, mat);
        if (arr[1] == 0 || arr[1] == 10) {
            return false;
        } else if (mat[arr[0]][arr[1] + 1] != '-' || mat[arr[0]][arr[1] - 1] != '-') {
            return false;
        }
    } else {
        cerr << "this move not exist";
        exit(1);
    }
    return true;
}

//wall
char **Board::wall(char **mat, char player, string move_like) {
    int *arr = new int[2];
    arr = find_player(player, mat);
    if (move_like == "up" || move_like == "down") {
        if (valid_wall(mat, player, move_like)) {
            mat[arr[0]][arr[1]] = 'w';
            mat[arr[0] + 1][arr[1]] = 'w';
            mat[arr[0] - 1][arr[1]] = 'w';
            return mat;
        } else {
            cerr << "you cant put a wall in this section";
            exit(1);
        }
    } else {
        if (valid_wall(mat, player, move_like)) {
            mat[arr[0]][arr[1] + 1] = 'w';
            mat[arr[0]][arr[1] + 1] = 'w';
            mat[arr[0]][arr[1] - 1] = 'w';
            return mat;
        } else {
            cerr << "you cant put a wall in this section";
            exit(1);
        }
    }
    return mat;
}

string Board::JsonConvertToBoard() {

    map<string, char[][2]> dataw;
    map<string, int[2]> datap;
    int NumberOfWall = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (mat[i][j] == 'w') {
                NumberOfWall++;
            }
        }

    }
    int NumberOfWall1 = 0;
    char wall[NumberOfWall][2];
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (mat[i][j] == 'w') {
                wall[NumberOfWall1][0] = i;
                wall[NumberOfWall1][1] = j;

                NumberOfWall1++;
            }
            string player = "pl";
            player += to_string(mat[i][j]);
            datap[player][0] = i;
            datap[player][1] = j;

        }

    }


}