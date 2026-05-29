#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QItemSelection>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(7,4,this);
    for(int row = 0;row<7;row++){
        for(int col = 0;col<4;col++){
            QStandardItem* item = new QStandardItem(QString("%1").arg(row*4+col));
            model->setItem(row,col,item);
        }
    }

    _table_view = new QTableView(this);
    _table_view->setModel(model);
    setCentralWidget(_table_view);
    this->resize(800,800);


    QItemSelectionModel* selection_model = _table_view->selectionModel();
    //定义左上角、右下角索引
    QModelIndex topLeft;
    QModelIndex bottomRight;
    topLeft = model->index(1,1,QModelIndex());
    bottomRight = model->index(5,2,QModelIndex());

    QItemSelection selection(topLeft,bottomRight);
    selection_model->select(selection,QItemSelectionModel::Select);


    //多个View共享模型
    QTableView* tableView2;
    tableView2 = new QTableView();
    tableView2->setWindowTitle(tr("tableView2"));
    tableView2->resize(400,300);
    tableView2->setModel(model);
    tableView2->setSelectionModel(selection_model);
    tableView2->show();
    tableView2->setAttribute(Qt::WA_DeleteOnClose);


    ui->mainToolBar->addAction(tr("当前项目"),this,&MainWindow::getCurrentItem);
    ui->mainToolBar->addAction(tr("切换选中"),this,&MainWindow::toggleSelection);


    //选择模型的选择条目更改后触发updateSelection函数
    connect(selection_model,&QItemSelectionModel::selectionChanged,this,&MainWindow::updateSelection);
    //选择模型改变后，当前项目也会改变，会触发changeCurrent函数
    connect(selection_model,&QItemSelectionModel::currentChanged,this,&MainWindow::changeCurrent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCurrentItem()
{
    auto currentData = _table_view->selectionModel()->currentIndex().data().toString();
    qDebug()<<tr("当前项目的内容")<<currentData;
}

void MainWindow::toggleSelection()
{
    //根节点下第1行第1列的索引
    QModelIndex topLeft = _table_view->model()->index(0,0,QModelIndex());
    auto max_row = _table_view->model()->rowCount(QModelIndex());
    auto max_col = _table_view->model()->columnCount(QModelIndex());
    //根据行号和列号获取右下角索引
    QModelIndex bottomRight = _table_view->model()->index(max_row-1,max_col-1,QModelIndex());

    //设置选择区域
    QItemSelection curSelection(topLeft,bottomRight);
    _table_view->selectionModel()->select(curSelection,QItemSelectionModel::Toggle);
}

void MainWindow::updateSelection(QItemSelection selected, QItemSelection deselected)
{
    QModelIndexList list = selected.indexes();
    for(int i = 0;i < list.size();i++){
        QString text = QString("(%1, %2)").arg(list[i].row()).arg(list[i].column());
        _table_view->model()->setData(list[i],text);
    }

    list = deselected.indexes();
    for(auto index:list){
        _table_view->model()->setData(index,"");
    }
}

void MainWindow::changeCurrent(QModelIndex current, QModelIndex previous)
{
    qDebug()<<tr("move (%1,%2) to (%3,%4)").arg(previous.row()).arg(previous.column())
                    .arg(current.row()).arg(current.column());

}