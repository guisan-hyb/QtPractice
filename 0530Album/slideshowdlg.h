#ifndef SLIDESHOWDLG_H
#define SLIDESHOWDLG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class SlideShowDlg;
}

class SlideShowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SlideShowDlg(QTreeWidgetItem* first_item,QTreeWidgetItem* last_item,QWidget *parent = nullptr);
    ~SlideShowDlg();

private:
    Ui::SlideShowDlg *ui;
    QTreeWidgetItem* _first_item;
    QTreeWidgetItem* _last_item;

public slots:
    void SlotSlideNext();
    void SlotSlidePre();

private slots:
    void SlotCloseBtnClicked();
};

#endif // SLIDESHOWDLG_H
