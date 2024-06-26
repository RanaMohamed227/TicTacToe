#include "login.h"
#include "ui_login.h"
#include <fstream>
#include <QMessageBox>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

QString login::getUsername() const {
    return ui->lineEdit_username->text();
}

QString login::getPassword() const {
    return ui->lineEdit_password->text();
}

void login::on_pushButton_clicked()
{
    QString username = getUsername();
    QString password = getPassword();
    std::ifstream file("mydata.txt");
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string savedUsername, savedPassword;
        if (std::getline(iss, savedUsername, ',') && std::getline(iss, savedPassword)) {
            if (QString::fromStdString(savedUsername) == username && QString::fromStdString(savedPassword) == password) {
                found = true;
                break;
            }
        }
    }
    file.close();

    if (found) {
        QMessageBox::information(this, "Login", "Login successful!");
        emit logInSuccessful();
        this->hide();
    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password!");
    }
}

void login::on_pushButton_2_clicked()
{
    emit signUpRequested();
}
