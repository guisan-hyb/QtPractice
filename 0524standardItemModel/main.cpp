#include "mainwindow.h"

#include <QApplication>
#include <QStandardItemModel>
#include <QPixmap>
#include <QTreeView>
#include <QListView>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    QStandardItemModel model;
    auto parentItem = model.invisibleRootItem();

    QStandardItem* item0 = new QStandardItem();
    item0->setText("item0");
    QPixmap pixmap0(50,50);
    pixmap0.fill(Qt::red);
    item0->setIcon(pixmap0);
    item0->setToolTip("indexA");
    parentItem->appendRow(item0);

    parentItem = item0;

    QStandardItem* item1 = new QStandardItem();
    item1->setText("item1");
    QPixmap pixmap1(50,50);
    pixmap1.fill(Qt::blue);
    item1->setIcon(pixmap1);
    item1->setToolTip("indexB");
    parentItem->appendRow(item1);

    QStandardItem* item2 = new QStandardItem();
    item2->setText("item2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    item2->setIcon(pixmap2);
    item2->setToolTip("indexC");
    parentItem->appendRow(item2);

    auto item3 = new QStandardItem();
    item3->setData("item3",Qt::EditRole);
    item3->setData("indexD",Qt::ToolTipRole);
    QPixmap pixmap3(50,50);
    pixmap3.fill(Qt::gray);
    item3->setData(QIcon(pixmap3),Qt::DecorationRole);
    parentItem->appendRow(item3);

    //取出根节点下第0行第0列的item的模型索引
    //此处列是为了统一操作；若为表格视图，则有行有列；
    QModelIndex indexA = model.index(0,0,QModelIndex());
    qDebug()<<" model indexA row count is "<<model.rowCount(indexA);

    //获取indexA下的0行0列
    QModelIndex indexB = model.index(0,0,indexA);
    qDebug()<<" indexB text is "<<model.data(indexB,Qt::EditRole).toString();
    qDebug()<<" indexB icon is "<<model.data(indexB,Qt::DecorationRole);
    qDebug()<<" indexB tool tip is "<<model.data(indexB,Qt::ToolTipRole).toString();

    //获取indexA下的1行0列
    QModelIndex indexC = model.index(1,0,indexA);
    qDebug()<<" indexC text is "<<model.data(indexC,Qt::EditRole).toString();
    qDebug()<<" indexC icon is "<<model.data(indexC,Qt::DecorationRole);
    qDebug()<<" indexC tool tip is "<<model.data(indexC,Qt::ToolTipRole).toString();

    QTreeView view;
    view.setModel(&model);
    view.show();

    return QCoreApplication::exec();
}
