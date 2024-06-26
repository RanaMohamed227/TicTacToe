#include <QApplication>
#include <QIcon>
#include "widget.h"
#include "board.h"
#include "agent.h"
#include "humanplayer.h"
#include "game.h"
#include "login.h"
#include "startup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create players and game state
    Player *player1 = new HumanPlayer(1);
    Player *player2 = new HumanPlayer(2);
    Player *player3 = new Agent(1);
    Player *player4 = new Agent(2);
    GameState *state = new GameState(9, player1->getPlayerNumber());

    // Create board, game, and widget
    Board *board = new Board(state);
    Game *game = new Game(player1, player2, player3, player4, board, state);
    Widget *window = new Widget(board, game);

    // Set parent for board
    board->setParent(window);
    window->setWindowTitle("Tic Tac Toe");

    // Create login window
    login *loginwindow = new login();
    loginwindow->show();

    // Connect signals for login success
    QObject::connect(loginwindow, &login::logInSuccessful, [=](){
        loginwindow->hide(); // Close the sign-up page
        window->show(); // Show the game board
        game->nextRound(); // Start the game
    });

    // Create startup page
    startup *startupPage = new startup();

    // Connect signals for sign up and login requests
    QObject::connect(loginwindow, &login::signUpRequested, [=]() {
        loginwindow->hide(); // Close the login window
        startupPage->show();
    });

    QObject::connect(startupPage, &startup::signUpSuccessful, [=](){
        startupPage->hide(); // Hide the sign-up page
        loginwindow->show();
    });

    QObject::connect(startupPage, &startup::logInRequested, [=]() {
        startupPage->hide(); // Close the startup page
        loginwindow->show(); // Show the login window again
    });

    return a.exec();
}
