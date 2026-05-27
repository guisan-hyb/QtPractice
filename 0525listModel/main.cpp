#include "mainwindow.h"

#include <QApplication>
#include <QStringList>
#include <QListView>
#include <QTableView>
#include "stringlistmodel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    QStringList list;
    list<<"a"<<"b"<<"c";
    StringListModel model(list);
    model.insertRows(3,2);
    model.removeRows(1,1);

    QTableView tableView;
    tableView.setModel(&model);
    tableView.show();

    QListView listView;
    listView.setModel(&model);
    listView.show();

    return QCoreApplication::exec();
}
