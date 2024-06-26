#ifndef STARTUP_H
#define STARTUP_H

#include <QWidget>

namespace Ui {
class startup;
}

class startup : public QWidget
{
    Q_OBJECT

public:
    explicit startup(QWidget *parent = nullptr);
    ~startup();

    QString getUsername() const;
    QString getPassword() const;

signals:
    void signUpSuccessful();
    void logInRequested();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::startup *ui;
};

#endif // STARTUP_H
