// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QtSql/QSqlError>

class DatabaseManager {
public:
    DatabaseManager() {
        // Connect to SQLite database
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("game_moves.db");
        if (!db.open()) {
            qDebug() << "Error: Failed to open database:" << db.lastError().text();
        }
    }

    void saveMove(int move, int player) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO moves (move, player) VALUES (:move, :player)");
        query.bindValue(":move", move);
        query.bindValue(":player", player);
        if (!query.exec()) {
            qDebug() << "Error saving move:" << query.lastError().text();
        }
    }

    QList<QPair<int, int>> getMoves() {
        QList<QPair<int, int>> moves;
        QSqlQuery query("SELECT * FROM moves", db);
        while (query.next()) {
            int move = query.value(0).toInt();
            int player = query.value(1).toInt();
            moves.append(qMakePair(move, player));
        }
        return moves;
    }

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

