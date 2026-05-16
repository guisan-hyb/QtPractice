#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qt4 方式连接信号和槽函数
    //connect(ui->showChildButton,SIGNAL(clicked(bool)),this,SLOT(showChildDialog()));


    _child_dialog = new childDialog(this);
    connect(ui->showChildButton,&QPushButton::clicked,this,&MainWindow::showChildDialog);//qt5风格：
    connect(_child_dialog,&childDialog::showMainSig,this,&MainWindow::showMainDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(_child_dialog){
        delete _child_dialog;
        _child_dialog = nullptr;
    }
}

void MainWindow::showChildDialog()
{
    // auto childDialog = new QDialog(this);
    // childDialog->show();
    _child_dialog->show();
    this->hide();
}

void MainWindow::showMainDialog()
{
    this->show();
    _child_dialog->hide();
}
