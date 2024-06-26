#include "agent.h"

Agent::Agent(int p) {
    logic = new GameLogic();
    playerNumber = p;
    human = false;
}

Agent::~Agent() {
    delete logic;
}

bool Agent::isHuman() {
    return human;
}

int Agent::getPlayerNumber() {
    return playerNumber;
}

void Agent::generateNextMove(int& move, GameState *state) {
    move = minimax(state);
}

int Agent::maxValue(GameState *state, int depth) {
    int newDepth = depth + 1;
    if (logic->gameWon(state)) {
        return -1;
    }
    if (logic->gameOver(state)) {
        return 0;
    }

    int vmSize = logic->numOfValidMoves(state);
    int validMoves[state->getBoardSize()];
    logic->generateValidMoves(state, validMoves);

    int bestScore = -1000; // Assume a very low initial score

    for (int i = 0; i < vmSize; i++) {
        GameState *nState = new GameState(state->getBoardSize(), state->getCurrentPlayer());
        state->deepCopy(nState);
        nState->makeMove(validMoves[i]);

        int score = minValue(nState, newDepth);
        if (score > bestScore) {
            bestScore = score;
        }

        delete nState;
    }

    return bestScore;
}

int Agent::minValue(GameState *state, int depth) {
    int newDepth = depth + 1;
    if (logic->gameWon(state)) {
        return 1;
    }
    if (logic->gameOver(state)) {
        return 0;
    }

    int vmSize = logic->numOfValidMoves(state);
    int validMoves[state->getBoardSize()];
    logic->generateValidMoves(state, validMoves);

    int bestScore = 1000; // Assume a very high initial score

    for (int i = 0; i < vmSize; i++) {
        GameState *nState = new GameState(state->getBoardSize(), state->getCurrentPlayer());
        state->deepCopy(nState);
        nState->makeMove(validMoves[i]);

        int score = maxValue(nState, newDepth);
        if (score < bestScore) {
            bestScore = score;
        }

        delete nState;
    }

    return bestScore;
}

int Agent::minimax(GameState *state) {
    int bestMove = -1;
    int bestScore = -1000; // Assume a very low initial score

    int vmSize = logic->numOfValidMoves(state);
    int validMoves[state->getBoardSize()];
    logic->generateValidMoves(state, validMoves);

    for (int i = 0; i < vmSize; i++) {
        GameState *nState = new GameState(state->getBoardSize(), state->getCurrentPlayer());
        state->deepCopy(nState);
        nState->makeMove(validMoves[i]);

        int score = minValue(nState, 0); // Start minimax with depth 0
        if (score > bestScore) {
            bestScore = score;
            bestMove = validMoves[i];
        }

        delete nState;
    }

    return bestMove;
}

