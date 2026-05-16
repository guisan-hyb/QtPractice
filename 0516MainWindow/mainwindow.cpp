#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QMenu>
#include <QIcon>
#include <QKeySequence>
#include <QDebug>
#include <QActionGroup>
#include "myaction.h"
#include <QToolButton>
#include <QSpinBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu* editMenu = ui->menubar->addMenu(tr("编辑(&E)"));
    editMenu->addSeparator();
    QAction* action_Open = editMenu->addAction(QIcon(":/res/jianchi.ico"),tr("打开文件(&O)"));
    action_Open->setShortcut(QKeySequence("Ctr+O"));
    connect(action_Open,&QAction::triggered,this,&MainWindow::on_actionEdit_triggered);

    QActionGroup * group = new QActionGroup(this);
    QAction* action_L = group->addAction(tr("左对齐(&L)"));
    action_L->setCheckable(true);
    QAction* action_R = group->addAction(tr("右对齐(&R)"));
    action_R->setCheckable(true);
    QAction* action_C = group->addAction(tr("居中(&C)"));
    action_C->setCheckable(true);
    editMenu->addSeparator();
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);

    MyAction* action = new MyAction(this);
    editMenu->addAction(action);

    connect(action,&MyAction::getText,this,&MainWindow::slot_set_text);

    QToolButton* toolbtn = new QToolButton(this);
    toolbtn->setText(tr("颜色"));
    ui->toolBar->addWidget(toolbtn);
    QMenu* colorMenu = new QMenu(this);
    colorMenu->addAction(tr("红色"));
    colorMenu->addAction(tr("绿色"));
    toolbtn->setMenu(colorMenu);
    toolbtn->setPopupMode(QToolButton::MenuButtonPopup);

    ui->toolBar->addSeparator();
    QSpinBox* spinbox = new QSpinBox(this);
    ui->toolBar->addWidget(spinbox);

    //临时状态信息：
    ui->statusbar->showMessage(tr("欢迎使用多文档编辑器"),2000);
    //永久显示状态标签
    QLabel* permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText(tr("柳贯一"));
    ui->statusbar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionshowDock_D_triggered()
{
    qDebug()<<"显示dock widget"<<Qt::endl;
    ui->dockWidget->show();
}


void MainWindow::on_actionNew_N_triggered()
{
    QTextEdit* textEdit = new QTextEdit(this);
    auto childWindow = ui->mdiArea->addSubWindow(textEdit);
    childWindow->setWindowTitle(tr("文本编辑子窗口"));
    childWindow->show();
}

void MainWindow::on_actionEdit_triggered()
{
    qDebug()<<"打开文件..."<<Qt::endl;
}

void MainWindow::slot_set_text(const QString &string)
{
    ui->textEdit->setText(string);
}

