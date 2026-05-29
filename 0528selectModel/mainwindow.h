#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>

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
    QTableView* _table_view;

private slots:
    void getCurrentItem();
    void toggleSelection();
    void updateSelection(QItemSelection selected, QItemSelection deselected);
    void changeCurrent(QModelIndex current, QModelIndex previous);
};
#endif // MAINWINDOW_H
