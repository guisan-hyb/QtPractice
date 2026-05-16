#include "maindialog.h"

#include <QApplication>
#include "childdialog.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    ChildDialog childDlg;
    auto ret = childDlg.exec();
    if(ret==QDialog::Accepted){
        qDebug()<<"Child Dialog exec returned, ret is "<<ret<<Qt::endl;
        w.show();
        a.exec();
    }else{
        qDebug()<<"Child Dialog exit, ret is "<<ret<<Qt::endl;
        return 0;
    }

    //w.show();
    //return QCoreApplication::exec();
}
