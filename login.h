
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <sstream>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    QString getUsername() const;
    QString getPassword() const;

signals:
    void logInSuccessful();
    void signUpRequested();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
