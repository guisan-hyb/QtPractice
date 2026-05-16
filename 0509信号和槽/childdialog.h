#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>

namespace Ui {
class childDialog;
}

class childDialog : public QDialog
{
    Q_OBJECT

signals:
    void showMainSig();

public:
    explicit childDialog(QWidget *parent = nullptr);
    ~childDialog();

private:
    Ui::childDialog *ui;
    QWidget* _parent;

public slots:
    void showMainWindow();
};

#endif // CHILDDIALOG_H
