#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void showTextFrame();
    void showTextBlock();
    void setTextFont(bool);
    void insertTable();
    void insertImage();
    void insertList();
    void textFind();
    void findNext();

private:
    Ui::MainWindow *ui;
    QDialog* findDialog;
    QLineEdit* lineEdit;
};
#endif // MAINWINDOW_H
