#include "startup.h"
#include "ui_startup.h"
#include <fstream>
#include <QString>
#include <QMessageBox>

startup::startup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::startup)
{
    ui->setupUi(this);
}

startup::~startup()
{
    delete ui;
}

QString startup::getUsername() const {
    return ui->lineEdit_username->text();
}

QString startup::getPassword() const {
    return ui->lineEdit_password->text();
}

void startup::on_pushButton_clicked()
{
    QString username = getUsername();
    QString password = getPassword();

    std::ofstream file("mydata.txt", std::ios::app);
    file << username.toStdString() << "," << password.toStdString() << std::endl;
    file.close();

    QMessageBox::about(this, "Sign Up", "Sign Up is successful!\n\nLog In to play!");
    emit signUpSuccessful();
    this->hide();
}

void startup::on_pushButton_2_clicked()
{
    emit logInRequested();
}
