#include <QApplication>
#include <QDialog>
#include <QLabel>
//#include "ui_hellodialog.h"
//#include "hellodialog.h"
#include "hellodialog2.h"

int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    // QDialog w;
    // QLabel label(&w);
    // label.setText("Hello World");
    // w.resize(400,300);
    // label.move(120,120);

    // Ui::Dialog ui;
    // ui.setupUi(&w);
    //HelloDialog dialog;
    //dialog.show();

    HelloDialog2 dialog;
    dialog.show();

    // w.show();
    return a.exec();
}