#include <iostream>
#include <string>
#include <map>


using namespace std;

class Board {
private:
    int num_of_players;

public:
    static Board currentBoard;
    char **mat;

    Board(int num_of_players);

    char **create_board(int num_of_players);

    char **set_empty(char **mat);

    void print_board(char **mat);

    int *find_player(char player, char **mat);

    bool valid_move(char **mat, char player, string move);

    bool moveUp(char **mat, char player);

    bool moveDown(char **mat, char player);

    bool moveLeft(char **mat, char player);

    bool moveRight(char **mat, char player);

    bool validWall(char **mat, char player, string move_like);

    bool wall(char **mat, char player, string move_like);

    string convertBoardToString();
    void convertStringToBoard(const string& board);

    Board();
};
