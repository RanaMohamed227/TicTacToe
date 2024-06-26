#include "game.h"

Game::Game(Player *player1, Player *player2, Player *player3, Player *player4, Board *board, GameState *state, QWidget *parent)
    : QWidget(parent)
{
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = player3;
    this->player4 = player4;
    this->currentPlayer1 = player1;
    this->currentPlayer2 = player3;
    this->nextPlayer1 = player1;
    this->nextPlayer2 = player3;
    this->currentPlayer = currentPlayer1;
    this->board = board;
    this->state = state;
    logic = new GameLogic();
    nextMove = -1;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Game::nextRound);

    // Load game histories from file on application startup
    loadGameHistoriesFromFile("game_histories.txt");
}

void Game::changeNextPlayer1(QString s) {
    if (s == "Human") {
        this->nextPlayer1 = player1;
    } else if (s == "Computer") {
        this->nextPlayer1 = player3;
    }
}

void Game::changeNextPlayer2(QString s) {
    if (s == "Human") {
        this->nextPlayer2 = player2;
    } else if (s == "Computer") {
        this->nextPlayer2 = player4;
    }
}

void Game::changePlayers() {
    if (currentPlayer == currentPlayer1) {
        currentPlayer = currentPlayer2;
    } else if (currentPlayer == currentPlayer2) {
        currentPlayer = currentPlayer1;
    }
}

void Game::restart() {
    this->currentPlayer1 = this->nextPlayer1;
    this->currentPlayer2 = this->nextPlayer2;
    this->currentPlayer = this->currentPlayer1;
    state->initiate();
    board->clicked = -1;
    board->update();
    nextRound();
    gameMoves.clear(); // Clear previous moves
}

void Game::nextRound() {
    delay(100);
    if (!(logic->gameOver(state) || logic->gameWon(state))) {
        if (currentPlayer->isHuman()) {
            board->setAllowed(true);
            board->getClicked(nextMove);
            if (nextMove != -1) {
                setNextMove(nextMove);
            } else {
                timer->start(100);
            }
        } else if (!currentPlayer->isHuman()) {
            currentPlayer->generateNextMove(nextMove, state);
            setNextMove(nextMove);
        }
    } else {
        timer->stop();
        int winner = state->otherPlayer(state->getCurrentPlayer());
        if (logic->gameWon(state)) {
            qDebug() << "The game has ended, and Player " << winner << " has won!";
        } else {
            qDebug() << "It's a draw! No more moves are possible.";
        }
        // Save game moves to the game list
        gameList.append(gameMoves.join(","));
        if (gameList.size() > 10) {
            gameList.removeFirst();
        }
        // Add game history to the list
        addGameHistory(gameMoves.join(","));
        gameMoves.clear(); // Clear moves for the next game
    }
}

void Game::setNextMove(int &move) {
    nextMove = move;
    int vmSize = logic->numOfValidMoves(state);
    int validMoves[vmSize];
    logic->generateValidMoves(state, validMoves);

    if (logic->validMove(nextMove, validMoves, vmSize, state)) {
        board->setAllowed(false);
        state->makeMove(nextMove);
        state->printBoard();
        QString moveStr = QString("%1%2").arg(currentPlayer->getPlayerNumber() == 1 ? "x" : "o").arg(nextMove);
        gameMoves.append(moveStr); // Save the move
        board->update();
        changePlayers();
        nextRound();
    }
    nextMove = -1;
}

void Game::delay(int ms) {
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Game::addGameHistory(const QString& history) {
    QString gameID = QString("ID%1").arg(gameList.size() + 1); // Generate game ID
    if (gameList.size() >= 10) {
        gameList.removeFirst(); // Remove the oldest game history
    }
    gameList.append(gameID + ": " + history);

    // Save to file immediately after adding new history
    saveGameHistoriesToFile("game_histories.txt");
}

void Game::replayGame(const QString& gameID) {
    // Find the game moves based on gameID
    QStringList moves;
    foreach (const QString &game, gameList) {
        if (game.startsWith(gameID)) {
            moves = game.split(",");
            break;
        }
    }
    if (moves.isEmpty()) {
        qDebug() << "Game not found!";
        return;
    }

    // Replay the game
    restart();
    qDebug() << "Replaying " << gameID;
    for (const QString &move : moves) {
        int pos = move.mid(2).toInt();
        int player = move.startsWith("x") ? 1 : 2;
        state->makeMove(pos);
        state->printBoard();
        QString moveStr = QString("%1%2").arg(player == 1 ? "x" : "o").arg(pos);
        gameMoves.append(moveStr);
        changePlayers();
    }

    int winner = state->otherPlayer(state->getCurrentPlayer());
    if (logic->gameWon(state)) {
        qDebug() << "The game has ended, and Player " << winner << " has won!";
    } else {
        qDebug() << "It's a draw! No more moves are possible.";
    }
}

void Game::saveGameHistoriesToFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Error: Could not open file for saving game histories";
        return;
    }

    QTextStream out(&file);
    for (const QString& history : gameList) {
        out << history << "\n";  // Write each game history to the file
    }

    file.close();
}

void Game::loadGameHistoriesFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open file for loading game histories";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString history = in.readLine();
        gameList.append(history);  // Load each game history from the file
    }

    file.close();
}
