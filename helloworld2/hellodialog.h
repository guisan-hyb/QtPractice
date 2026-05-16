#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>
#include "ui_hellodialog.h"

class HelloDialog : public QDialog
{
public:
    HelloDialog();
    ~HelloDialog();
private:
    Ui::Dialog* _ui;
};

#endif // HELLODIALOG_H
