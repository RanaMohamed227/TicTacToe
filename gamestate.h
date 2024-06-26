#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <cmath>

class GameState {
private:
    int boardSize;
    int *board;
    int player1;
    int player2;
    int currentPlayer;

public:
    GameState(int n, int player);
    ~GameState();
    void printBoard();
    void makeMove(int& move);
    void changePlayer();
    int otherPlayer(int currentPlayer);
    void initiate();
    void deepCopy(GameState* copy); // Declaration of deepCopy

    int getBoardSize();
    int* getBoard();
    int getCurrentPlayer();
};

#endif // GAMESTATE_H
