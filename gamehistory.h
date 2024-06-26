#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <QString>
#include <queue>
#include <vector>

struct GameSession {
    int id;
    QString player1;
    QString player2;
    int winner; // 0 for draw, 1 for player 1, 2 for player 2
    std::queue<int> moves; // Queue to store moves
};

class GameHistory {
public:
    GameHistory();

    void addGame(const QString& player1, const QString& player2, int winner, const std::queue<int>& moves);
    std::vector<GameSession> loadGames() const;

private:
    std::vector<GameSession> games;
    int nextID;
};

#endif // GAMEHISTORY_H
