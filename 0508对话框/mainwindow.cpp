#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //法一：
    // auto w = new QDialog(this);
    // w->setModal(1);//true为模态，false为非模态
    // w->show();

    // 法二：
    // QDialog w;
    // w.exec();

    //窗口置顶
    auto s = new QDialog(this);
    s->setWindowFlag(Qt::WindowStaysOnTopHint);
    s->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
