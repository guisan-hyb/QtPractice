#include "widget.h"
#include "ui_widget.h"
#include <QCursor>
#include <QMouseEvent>
#include <QApplication>
#include <QPixmap>
#include <QWheelEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //如果是鼠标左键按下
    if(event->button()==Qt::LeftButton){
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        offset = event->globalPosition().toPoint() - pos();
    }
    else if(event->button()==Qt::RightButton){
        QCursor cursor(QPixmap(":/jianchi.jpg"));
        QApplication::setOverrideCursor(cursor);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(windowState() == Qt::WindowFullScreen){
            setWindowState(Qt::WindowNoState);
        }
        else{
            setWindowState(Qt::WindowFullScreen);
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //在鼠标移动过程中，保证窗口也移动
    if(event->buttons() & Qt::LeftButton){
        QPoint windows = event->globalPosition().toPoint() - offset;
        this->move(windows);
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0){
        ui->textEdit->zoomIn();
    }
    else{
        ui->textEdit->zoomOut();
    }
}
