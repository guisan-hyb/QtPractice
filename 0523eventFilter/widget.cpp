#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QWheelEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    line_edit_ = new MyEdit(this);
    line_edit_->move(100,100);

    line_edit_->installEventFilter(this);
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *)
{
    qDebug()<<"widget key press event";
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==line_edit_){
        if(event->type()==QEvent::KeyPress){
            qDebug()<<"widget eventfilter catch line_edit_";
            return false;
        }
    }

    if(watched==ui->textEdit){
        if(event->type()==QEvent::Wheel){
            QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
            if(wheelEvent->angleDelta().y() > 0){
                qDebug()<<"catch wheel event delta > 0"<<Qt::endl;
                ui->textEdit->zoomIn();
            }else{
                qDebug()<<"catch wheel event delta < 0"<<Qt::endl;
                ui->textEdit->zoomOut();
            }
            return true;
        }
        return false;
    }

    if(watched==ui->spinBox){
        if(event->type()==QEvent::KeyPress){
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key()==Qt::Key_Space){
                ui->spinBox->setValue(0);
                return true;
            }
            return false;
        }
        return false;
    }

    return QWidget::eventFilter(watched,event);
}
