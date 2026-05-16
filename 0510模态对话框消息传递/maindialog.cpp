#include "maindialog.h"
#include "ui_maindialog.h"
#include "childdialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_enterChildBtn_clicked()
{
    close();//并没有退出，只有所有界面都不显示了才回收
    ChildDialog childDlg;
    if(childDlg.exec()==QDialog::Accepted){
        this->show();
    }else{
        return;
    }
}

