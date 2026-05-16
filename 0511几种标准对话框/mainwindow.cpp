#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
//#include <QProgressDialog>
#include <QWizard>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _counter=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_colorBtn_clicked()
{
    QColorDialog colorDlg(Qt::blue,this);
    colorDlg.setOption(QColorDialog::ShowAlphaChannel);
    colorDlg.exec();
    QColor color = colorDlg.currentColor();
    qDebug()<<"color is"<<color<<Qt::endl;
}


void MainWindow::on_pushButton_clicked()
{
    QString path = QDir::currentPath();
    QString title = tr("文件对话框");
    QString filter = tr("文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this,title,path,filter);

    qDebug()<<aFileName<<Qt::endl;
}


void MainWindow::on_pushButton_2_clicked()
{
    bool ok = false;
    auto intdata = QInputDialog::getInt(this,tr("数字输入对话框"),tr("请输入提示"),200,-200,400,10,&ok);
    if(ok){
        qDebug()<<intdata<<Qt::endl;
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    bool ok = false;
    auto floatdata = QInputDialog::getDouble(this,tr("浮点数输入对话框"),tr("请输入提示"),0.1,-2,4,2,&ok);
    if(ok){
        qDebug()<<floatdata<<Qt::endl;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QStringList item;
    item<<tr("条目一")<<tr("条目二");
    bool ok = false;
    auto itemData = QInputDialog::getItem(this,tr("条目对话框"),tr("输入或选择条目"),item,0,true,&ok);
    if(ok){
        qDebug()<<"item is" <<itemData<<Qt::endl;
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    auto ret = QMessageBox::question(this,tr("提问对话框"),tr("你是单身吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ret==QMessageBox::Yes){
        qDebug()<<"ret is"<<ret;
        qDebug()<<"hello";
    }else{
        return;
    }

    auto ret2 = QMessageBox::information(this,tr("通知对话框"),tr("你好"),QMessageBox::Yes);
    if(ret2==QMessageBox::Yes){
        qDebug()<<"ret2 is "<<ret2;
    }else{
        return;
    }

    auto ret3 = QMessageBox::warning(this,tr("警告对话框"),tr("en"),QMessageBox::Yes);
    if(ret3==QMessageBox::Yes){
        qDebug()<<"ret3 is "<<ret3;
    }
    else{
        return;
    }

    auto ret4 = QMessageBox::critical(this,tr("关键提示对话框"),tr("abcde"),QMessageBox::Ok);
    if(ret4 == QMessageBox::Ok){
        qDebug()<<"ret4 is "<<ret4;
    }else{
        return;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    _progressDialog = new QProgressDialog(tr("正在复制"),tr("取消复制"),0,5000,this);
    _progressDialog->setWindowTitle(tr("文件复制进度对话框"));
    _progressDialog->setWindowModality(Qt::ApplicationModal);
    _timer = new QTimer(this);
    connect(_timer,&QTimer::timeout,this,&MainWindow::on_updateProgressDialog);
    connect(_progressDialog,&QProgressDialog::canceled,this,&MainWindow::on_cancelProgressDialog);
    _timer->start(2);//每2ms触发一次定时器，调用槽函数
}

void MainWindow::on_updateProgressDialog(){
    _counter++;
    if(_counter>5000){
        _timer->stop();
        delete _timer;
        _timer=nullptr;
        delete _progressDialog;
        _progressDialog=nullptr;
        _counter=0;
        return;
    }

    _progressDialog->setValue(_counter);
}

void MainWindow::on_cancelProgressDialog(){
    _timer->stop();
    delete _timer;
    _timer=nullptr;
    delete _progressDialog;
    _progressDialog=nullptr;
    _counter=0;
    return;
}

void MainWindow::on_pushButton_7_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("全城热恋"));


    auto page1 = new QWizardPage();
    page1->setTitle(tr("婚恋介绍引导程序"));
    auto label1 = new QLabel();
    label1->setText(tr("该程序帮助你找到人生伴侣"));
    auto layout = new QVBoxLayout();
    layout->addWidget(label1);
    page1->setLayout(layout);
    wizard.addPage(page1);


    QWizardPage* page2 = new QWizardPage();
    page2->setTitle("选择心动类型");
    auto group = new QButtonGroup(page2);
    auto btn1 = new QRadioButton();
    btn1->setText("冬雪莲");
    group->addButton(btn1);

    auto btn2 = new QRadioButton();
    btn2->setText("塔菲");
    group->addButton(btn2);

    auto btn3 = new QRadioButton();
    btn3->setText("雨姐");
    group->addButton(btn3);

    auto btn4 = new QRadioButton();
    btn4->setText("白凝冰");
    group->addButton(btn4);

    auto layout2 = new QVBoxLayout();
    for(int i = 0;i < group->buttons().size(); i++){
        layout2->addWidget(group->buttons()[i]);
    }
    page2->setLayout(layout2);
    wizard.addPage(page2);


    QWizardPage* page3 = new QWizardPage();
    page3->setTitle(tr("你的缘分即将到来"));
    auto label3 = new QLabel();
    label3->setText(tr("感谢你的参与"));
    QVBoxLayout* layout3 = new QVBoxLayout();
    layout3->addWidget(label3);
    page3->setLayout(layout3);
    wizard.addPage(page3);

    wizard.show();
    wizard.exec();
}

