#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QStringList>

#include "board.h"
#include "login.h"

Widget::Widget(Board *board, Game *game, QWidget *parent)
    : QWidget(parent), currentGame(game)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout();
    QVBoxLayout *players = new QVBoxLayout();
    QHBoxLayout *buttons = new QHBoxLayout();

    statusLabel = new QLabel("Have Fun", this);

    QPushButton *quit = new QPushButton("Quit", this);
    QPushButton *restart = new QPushButton("Restart", this);

    connect(quit, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(restart, &QPushButton::clicked, game, &Game::restart);

    QStringList *pselection;
    pselection = new QStringList();
    pselection->append("");
    pselection->append("Human");
    pselection->append("Computer");

    combo1 = new QComboBox();
    combo1->addItems(*pselection);
    combo2 = new QComboBox();
    combo2->addItems(*pselection);

    connect(combo1, QOverload<int>::of(&QComboBox::activated), [=](int index) {
        QString text = combo1->itemText(index);
        game->changeNextPlayer1(text);
    });

    connect(combo2, QOverload<int>::of(&QComboBox::activated), [=](int index) {
        QString text = combo2->itemText(index);
        game->changeNextPlayer2(text);
    });

    loginwindow = new login(this);
    connect(loginwindow, &login::logInSuccessful, this, &Widget::showgameboard);
    hbox->addWidget(loginwindow);

    gameBoard = board;
    vbox->addWidget(loginwindow);
    vbox->addWidget(gameBoard);
    vbox->addWidget(statusLabel, 1, Qt::AlignTop);

    buttons->addWidget(restart);
    buttons->addWidget(quit);

    vbox->addLayout(buttons);

    hbox->addLayout(vbox);
    hbox->addLayout(players);

    players->addWidget(combo1, 0);
    players->addWidget(combo2, 1, Qt::AlignTop);

    setLayout(hbox);

    // Initialize game list and combo box for game selection
    gameSelectionComboBox = new QComboBox(this);
    vbox->addWidget(new QLabel("Select Game to Replay:", this));
    vbox->addWidget(gameSelectionComboBox);

    connect(gameSelectionComboBox, QOverload<int>::of(&QComboBox::activated), this, &Widget::handleGameSelection);

    // Populate the game list
    for (const QString& gameID : game->getGameList()) {
        gameSelectionComboBox->addItem(gameID);
    }
}

void Widget::showgameboard()
{
    loginwindow->setVisible(false); // Hide the sign-up page
    gameBoard->setVisible(true); // Show the game board

    // Update game list combo box
    gameSelectionComboBox->clear(); // Clear existing items
    QStringList gameIDs = currentGame->getGameList(); // Access gameList from Game class
    for (const QString& gameID : gameIDs) {
        gameSelectionComboBox->addItem(gameID); // Add gameIDs to the combo box
        std::cout<<"3";
    }
}


void Widget::handleGameSelection(int index)
{
    if (index >= 0 && index < gameSelectionComboBox->count()) {
        QString selectedGameID = gameSelectionComboBox->itemText(index);
        currentGame->replayGame(selectedGameID);
        std::cout<<"2";
    }
}

Widget::~Widget() {}
