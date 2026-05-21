#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QDebug>
#include <QList>
#include <QUrl>
#include <Qstring>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        qDebug()<<"event url is"<<event->mimeData()->urls()[0]<<Qt::endl;
        event->acceptProposedAction();
    }else{
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    //判断是否包含url
    if(mimeData->hasUrls()){
        QList<QUrl> urlList = mimeData->urls();
        //将第一个匹配的文件路径获取
        QString filename = urlList[0].toLocalFile();
        if(!filename.isEmpty()){
            QFile file(filename);
            if(!file.open(QIODevice::ReadOnly)){
                return;
            }
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
        }
    }else{
        event->ignore();
    }
}
