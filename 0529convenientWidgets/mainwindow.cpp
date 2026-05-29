#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QPixmap>
#include <QTableWidgetItem>
#include <QAbstractItemView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto listwidget = new QListWidget(this);
    auto listwidgetitem = new QListWidgetItem;
    listwidgetitem->setText("listitem");
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::blue);
    listwidgetitem->setIcon(pixmap);
    listwidgetitem->setToolTip("this is list item");
    listwidget->insertItem(1,listwidgetitem);

    auto listwidgetitem2 = new QListWidgetItem;
    listwidgetitem2->setText("listitem2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    listwidgetitem2->setIcon(pixmap2);
    listwidgetitem2->setToolTip("this is list item2");
    listwidget->insertItem(2,listwidgetitem2);

    listwidget->setSortingEnabled(true);
    listwidget->sortItems(Qt::DescendingOrder);

    listwidget->show();
    this->setCentralWidget(listwidget);

    //实现拖拽
    listwidget->setSelectionMode(QAbstractItemView::SingleSelection);
    listwidget->setDragEnabled(true);
    listwidget->viewport()->setAcceptDrops(true);
    listwidget->setDropIndicatorShown(true);
    listwidget->setDragDropMode(QAbstractItemView::InternalMove);



    _treeWidget = new QTreeWidget();
    _treeWidget->setColumnCount(2);
    QStringList headers;
    headers<<"name"<<"year";
    _treeWidget->setHeaderLabels(headers);

    auto grade1 = new QTreeWidgetItem(_treeWidget);
    grade1->setText(0,"Grade1");

    QTreeWidgetItem* student = new QTreeWidgetItem(grade1);
    student->setText(0,"Tom");
    student->setText(1,"1996");

    auto student2 = new QTreeWidgetItem(grade1,student);
    student2->setText(0,"Zack");
    student2->setText(1,"1988");

    auto grade2 = new QTreeWidgetItem(_treeWidget,grade1);
    grade2->setText(0,"Grade2");

    auto student3 = new QTreeWidgetItem(grade2);
    student3->setText(0,"Will");
    student3->setText(1,"2007");

    //删除student3
    auto parent_student3 = student3->parent();
    auto index_stu3 = parent_student3->indexOfChild(student3);
    delete parent_student3->takeChild(index_stu3);

    //删除grade2
    auto parent_grade2 = grade2->parent();
    assert(parent_grade2 == nullptr);
    auto index_grade2 = _treeWidget->indexOfTopLevelItem(grade2);
    delete _treeWidget->takeTopLevelItem(index_grade2);

    _treeWidget->show();



    _tableWidget = new QTableWidget(3,2);
    QTableWidgetItem* tablewidgetitem = new QTableWidgetItem("Qt");
    _tableWidget->setItem(1,1,tablewidgetitem);
    QTableWidgetItem* headerV = new QTableWidgetItem("first");
    _tableWidget->setVerticalHeaderItem(0,headerV);
    QTableWidgetItem* headerH = new QTableWidgetItem("ID");
    _tableWidget->setHorizontalHeaderItem(0,headerH);
    _tableWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _treeWidget;
    delete _tableWidget;
}
