#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include "board.h"
#include "game.h"
#include "login.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(Board *board, Game *game, QWidget *parent = 0);
    ~Widget();

private slots:
    void showgameboard();
    void handleGameSelection(int index);

private:
    QComboBox *combo1, *combo2;
    QLabel *statusLabel;
    login *loginwindow;
    Board *gameBoard;
    QComboBox *gameSelectionComboBox;
    QStringList gameList;
    Game *currentGame;
};

#endif // WIDGET_H
