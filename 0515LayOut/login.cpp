#include "login.h"
#include "ui_login.h"
#include "register.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    this->close();
    _register->show();
}

void Login::initSignals(){
    _register=std::make_shared<Register>();
    _register->set_login(shared_from_this());//用这个方法前提是要有一个智能指针
}
