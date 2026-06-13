#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

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

private:
    Ui::MainWindow *ui;
    QWidget* _protree;
    //这里使用QWidget而不是Protree，一是降低类与类之间的耦合性，二是防止互引用（万一Protree里也用到MainWindow了呢，当然这个问题也可以通过一些方式规避）
    //这里呢直接用基类，然后再通过dynamic_cast做转换
    //这样分开写实现了解耦，我树形界面面出问题不影响主界面的其他显示。
    //后期方便修改,新功能我只需要在Protree类中修改
    QWidget* _picshow;

protected:
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void SlotCreatePro(bool);
    void SlotOpenPro(bool);

signals:
    void SigOpenPro(const QString& path);
};
#endif // MAINWINDOW_H
