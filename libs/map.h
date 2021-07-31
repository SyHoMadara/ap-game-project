#include <iostream>
#include <string>
#include <map>


using namespace std;

class Board {
private:
    int numberOfPlayers;

public:
    static Board currentBoard;
    char **mat;

    Board(int numberOfPlayers);

   void createBoard(int num_of_players);

    void setEmptyMap();

    void printMap();

    int *findPlayer(char player);

    bool validMove( char player, string move);

    bool moveUp( char player);

    bool moveDown( char player);

    bool moveLeft( char player);

    bool moveRight(char player);

    bool validWall( char player, string move_like);

    bool wall( char player, string move_like);

    string convertBoardToString();
    void convertStringToBoard(const string& board);

    Board();
};
