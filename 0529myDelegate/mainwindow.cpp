#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include "spinboxdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto* model = new QStandardItemModel(7,4,this);
    for(int row = 0;row<7;row++){
        for(int col = 0;col<4;col++){
            QStandardItem* item = new QStandardItem(QString("%1").arg(row*4+col));
            model->setItem(row,col,item);
        }
    }

    QTableView* _tableView = new QTableView();
    _tableView->setModel(model);
    setCentralWidget(_tableView);
    this->resize(800,800);


    auto* model2 = new QStandardItemModel(7,4,this);
    for(int row = 0;row<7;row++){
        for(int col = 0;col<4;col++){
            QStandardItem* item = new QStandardItem(QString("%1").arg(row*4+col));
            model2->setItem(row,col,item);
        }
    }

    auto* delegate = new SpinBoxDelegate(this);
    _tableView2 = new QTableView();
    _tableView2->setModel(model);
    _tableView2->setItemDelegate(delegate);
    _tableView2->show();
    _tableView2->resize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _tableView2;
}
