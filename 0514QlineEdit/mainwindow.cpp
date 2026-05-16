#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString ip_mask = "000.000.000.000;_";
    ui->ip_lineEdit->setInputMask(ip_mask);

    QString mac_mask = "HH:HH:HH:HH;_";
    ui->mac_lineEdit->setInputMask(mac_mask);

    //ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
    ui->pwd_lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    QRegularExpression regx("[a-zA-Z0-9_-]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+");
    QValidator* validator = new QRegularExpressionValidator(regx,ui->email_lineEdit);
    ui->email_lineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}
