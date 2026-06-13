#ifndef PRELISTWID_H
#define PRELISTWID_H

#include <QListWidget>
#include <QTreeWidgetItem>

class PreListWid : public QListWidget
{
    Q_OBJECT
public:
    PreListWid(QWidget* parent = nullptr);
    virtual ~PreListWid();

private:
    void AddListItem(const QString& path);
    int _global;//记录照片数目
    int _last_index;
    QMap<QString,QListWidgetItem*> _set_item;
    QPoint _pos_origin;

public slots:
    void SlotUpPreList(QTreeWidgetItem* tree_item);
    void SlotUpSelected(QTreeWidgetItem* tree_item);
    void SlotItemPressed(QListWidgetItem* item);

signals:
    void SigUpSelectShow(QString& path);
};

#endif // PRELISTWID_H
