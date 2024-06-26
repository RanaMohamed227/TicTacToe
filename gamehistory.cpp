#include "gamehistory.h"

GameHistory::GameHistory() : nextID(1) {}

void GameHistory::addGame(const QString& player1, const QString& player2, int winner, const std::queue<int>& moves) {
    GameSession session;
    session.id = nextID++;
    session.player1 = player1;
    session.player2 = player2;
    session.winner = winner;
    session.moves = moves;

    games.push_back(session);
}

std::vector<GameSession> GameHistory::loadGames() const {
    return games;
}
