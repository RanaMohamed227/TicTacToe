#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "gamelogic.h"
#include "board.h"
#include "gamestate.h"
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <QTime>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Game : public QWidget
{
    Q_OBJECT

private:
    Player *player1;
    Player *player2;
    Player *player3;
    Player *player4;
    Player *currentPlayer;
    Player *currentPlayer1;
    Player *currentPlayer2;
    Player *nextPlayer1;
    Player *nextPlayer2;
    Board *board;
    GameLogic *logic;
    GameState *state;
    QTimer *timer;
    int nextMove;
    QStringList gameMoves;
    QStringList gameList;

    void setNextMove(int&);
    void saveGameHistoriesToFile(const QString& filename);
    void loadGameHistoriesFromFile(const QString& filename);

public:
    Game(Player*, Player*, Player*, Player*, Board*, GameState*, QWidget *parent = nullptr);
    void changePlayers();
    void delay(int);
    void addGameHistory(const QString& history);
    QStringList getGameList() const { return gameList; }
    void replayGame(const QString& gameID);

public slots:
    void nextRound();
    void restart();
    void changeNextPlayer1(QString);
    void changeNextPlayer2(QString);
};

#endif // GAME_H
