#include "protreeitem.h"
#include "const.h"

ProTreeItem::ProTreeItem(QTreeWidget *view, const QString &name, const QString &path, int type)
    : QTreeWidgetItem(view,type), _path(path), _name(name), _root(this), _pre_item(nullptr), _next_item(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidgetItem *parent, const QString &name, const QString &path, QTreeWidgetItem *root, int type)
    : QTreeWidgetItem(parent,type), _path(path),_name(name), _root(root),_pre_item(nullptr), _next_item(nullptr)
{

}

const QString &ProTreeItem::GetPath()
{
    return _path;
}

QTreeWidgetItem *ProTreeItem::GetRoot()
{
    return _root;
}

void ProTreeItem::SetPreItem(QTreeWidgetItem *item)
{
    _pre_item=item;
}

void ProTreeItem::SetNextItem(QTreeWidgetItem *item)
{
    _next_item=item;
}

ProTreeItem *ProTreeItem::GetPreItem()
{
    return dynamic_cast<ProTreeItem*>(_pre_item);
}

ProTreeItem *ProTreeItem::GetNextItem()
{
    return dynamic_cast<ProTreeItem*>(_next_item);
}

ProTreeItem *ProTreeItem::GetLastPicChild()
{
    if(this->type()==TreeItemPic){
        return nullptr;
    }

    auto child_count = this->childCount();
    if(child_count==0) return nullptr;

    for(int i = child_count-1;i>=0;i--){
        auto* last_child = this->child(i);
        auto* last_child_item = dynamic_cast<ProTreeItem*>(last_child);
        if(last_child_item->type()==TreeItemPic){
            return last_child_item;
        }

        last_child = last_child_item->GetLastPicChild();
        if(!last_child) continue;
        last_child_item = dynamic_cast<ProTreeItem*>(last_child);
        return last_child_item;
    }
    return nullptr;
}

ProTreeItem *ProTreeItem::GetFirstPicChild()
{
    if(this->type()==TreeItemPic) return nullptr;

    auto child_count = this->childCount();
    if(child_count==0) return nullptr;

    for(int i = 0;i<child_count;i++){
        auto* first_child = this->child(i);
        auto* first_child_item = dynamic_cast<ProTreeItem*>(first_child);
        if(first_child_item->type()==TreeItemPic){
            return first_child_item;
        }

        first_child = first_child_item->GetFirstPicChild();
        if(!first_child) continue;
        first_child_item = dynamic_cast<ProTreeItem*>(first_child);
        return first_child_item;
    }
    return nullptr;
}


