#ifndef MYEDIT_H
#define MYEDIT_H
#include <QLineEdit>
#include <QWidget>

class MyEdit: public QLineEdit
{
    Q_OBJECT
public:
    explicit MyEdit(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* );
    bool event(QEvent* event);
};

#endif // MYEDIT_H
