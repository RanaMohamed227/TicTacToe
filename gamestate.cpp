#include "gamestate.h"

GameState::GameState(int n, int player) {
    player1 = 1;
    player2 = 2;
    currentPlayer = player;
    boardSize = n;
    board = new int[boardSize];
    for (int i = 0; i < boardSize; i++) {
        board[i] = 0;
    }
}

GameState::~GameState() {
    delete[] board; // Corrected deletion for array allocation
}

void GameState::printBoard() {
    int a = sqrt(boardSize);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            if (board[a*i+j] == 0) {
                std::cout << "  ";
            }
            else if (board[a*i+j] == 1) {
                std::cout << "x ";
            }
            else if (board[a*i+j] == 2) {
                std::cout << "o ";
            }
        }
        std:: cout << "\n";
    }
}

int GameState::otherPlayer(int currentPlayer) {
    if (currentPlayer == player1) {
        return player2;
    }
    else if (currentPlayer == player2) {
        return player1;
    }
}

void GameState::changePlayer() {
    if (currentPlayer == player1) {
        currentPlayer = player2;
    }
    else if (currentPlayer == player2) {
        currentPlayer = player1;
    }
}

void GameState::makeMove(int &move) {
    board[move] = currentPlayer;
    changePlayer();
}

int GameState::getBoardSize() {
    return boardSize;
}

int* GameState::getBoard() {
    return board;
}

int GameState::getCurrentPlayer() {
    return currentPlayer;
}

void GameState::initiate() {
    for (int i = 0; i < boardSize; i++) {
        board[i] = 0;
    }
    currentPlayer = player1;
}

void GameState::deepCopy(GameState* copy) {
    // Check if the board sizes match
    if (copy->getBoardSize() != boardSize) {
        std::cerr << "Error: Board sizes do not match in deepCopy!" << std::endl;
        return;
    }

    // Copy the board state
    for (int i = 0; i < boardSize; i++) {
        copy->getBoard()[i] = board[i];
    }
}
