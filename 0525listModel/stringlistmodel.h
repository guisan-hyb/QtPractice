#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class StringListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    StringListModel(const QStringList& strings, QObject* parent = nullptr);
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QStringList stringList;
};

#endif // STRINGLISTMODEL_H
