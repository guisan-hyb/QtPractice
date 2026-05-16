#include "childdialog.h"
#include "ui_childdialog.h"
#include <QDebug>

ChildDialog::ChildDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChildDialog)
{
    ui->setupUi(this);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}

void ChildDialog::on_enterMainBtn_clicked()
{
    qDebug()<<tr("点击了进入主界面按钮")<<Qt::endl;
    accept();
}

