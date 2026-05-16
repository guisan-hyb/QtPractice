#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainDialog;
}
QT_END_NAMESPACE

class MainDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog() override;

private slots:
    void on_enterChildBtn_clicked();

private:
    Ui::MainDialog *ui;
};
#endif // MAINDIALOG_H
