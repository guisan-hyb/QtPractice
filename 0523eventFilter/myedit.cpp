#include "myedit.h"
#include <QDebug>
#include <QKeyEvent>

MyEdit::MyEdit(QWidget *parent) : QLineEdit(parent)
{

}

void MyEdit::keyPressEvent(QKeyEvent * event)
{
    qDebug()<<"MyEdit key press event";
    QLineEdit::keyPressEvent(event);//子类调用基类的该功能
    event->ignore();
}

bool MyEdit::event(QEvent *event)
{
    //只重写按键事件
    if(event->type()==QEvent::KeyPress){
        qDebug()<<tr("my edit event")<<Qt::endl;
        //return false;
    }

    //其他的事件交由基类处理
    return QLineEdit::event(event);
}
