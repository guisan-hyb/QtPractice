#include "prosetpage.h"
#include "ui_prosetpage.h"
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>

ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);
    registerField("proPath",ui->lineEdit_2);
    registerField("proName*",ui->lineEdit);//这里registerField()函数的第一个参数带*号表示这是一个必填字段
    connect(ui->lineEdit,&QLineEdit::textEdited,this,&ProSetPage::completeChanged);//触发isComplete()
    connect(ui->lineEdit_2,&QLineEdit::textEdited,this,&ProSetPage::completeChanged);
    QString curPath = QDir::currentPath();
    ui->lineEdit_2->setText(curPath);
    ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().size());

    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setClearButtonEnabled(true);
}

ProSetPage::~ProSetPage()
{
    delete ui;
}

void ProSetPage::GetProSetting(QString &name, QString& path)
{
    name = ui->lineEdit->text();
    path = ui->lineEdit_2->text();
}

bool ProSetPage::isComplete() const
{
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == ""){
        return false;
    }

    QDir dir(ui->lineEdit_2->text());
    if(!dir.exists()){
        ui->tips->setText("project path is not exist");
        return false;
    }

    //判断路径
    QString absFilePath = dir.absoluteFilePath(ui->lineEdit->text());//在 dir 这个目录下，找名为 ui->lineEdit->text() 的文件或文件夹，并返回它的绝对路径
    QDir dist_dir(absFilePath);
    if(dist_dir.exists()){
        ui->tips->setText("project has existed,change path or name");
        return false;
    }

    ui->tips->setText("");
    return QWizardPage::isComplete();
    //c++编程思路：重写了基类的函数，如果还想用基类的功能，子类再调用基类函数即可
}

void ProSetPage::on_pushButton_clicked()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle("选择导入的文件夹");
    auto path = QDir::currentPath();
    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }

    if(fileNames.length()<=0) return;

    QString import_path = fileNames.at(0);
    ui->lineEdit_2->setText(import_path);
}

