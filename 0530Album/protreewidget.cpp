#include "protreewidget.h"
#include <QDir>
#include <protreeitem.h>
#include "const.h"
#include "qheaderview.h"
#include <QGuiApplication>
#include <QMenu>
#include <QFileDialog>
#include "removeprodialog.h"
#include "slideshowdlg.h"

ProTreeWidget::ProTreeWidget(QWidget* parent)
    : QTreeWidget(parent),_right_btn_item(nullptr),_active_item(nullptr),_dialog_progress(nullptr),_open_progressdlg(nullptr)
    ,_selected_item(nullptr),_thread_create_pro(nullptr),_thread_open_pro(nullptr),
    _player(nullptr),_audioOutput(nullptr),_playlist(nullptr)
{
    this->header()->hide();
    connect(this,&ProTreeWidget::itemPressed,this,&ProTreeWidget::SlotItemPressed);

    _action_import = new QAction(QIcon(":/icon/import.png"),tr("导入文件"),this);
    _action_setstart = new QAction(QIcon(":/icon/core.png"),tr("设置活动项目"),this);
    _action_closepro = new QAction(QIcon(":/icon/close.png"),tr("关闭项目"),this);
    _action_slideshow = new QAction(QIcon(":/icon/slideshow.png"),tr("轮播图播放"),this);

    connect(_action_import,&QAction::triggered,this,&ProTreeWidget::SlotImport);
    connect(_action_setstart,&QAction::triggered,this,&ProTreeWidget::SlotSetActive);
    connect(_action_closepro,&QAction::triggered,this,&ProTreeWidget::SlotClosePro);
    connect(_action_slideshow,&QAction::triggered,this,&ProTreeWidget::SlotSlideShow);

    connect(this,&ProTreeWidget::itemDoubleClicked,this,&ProTreeWidget::SlotDoubleClickItem);

    //注：播放背景音乐为循环模式
}


//向导对话框完成之后
//会把路径和名字传给MainWindow
//MainWindow里面会调用这个函数，根据名字和路径先创建一个文件夹，并且把这个文件夹显示在左侧的目录上
void ProTreeWidget::AddProToTree(const QString &name, const QString &path)
{
    QDir dir(path);
    QString file_path = dir.absoluteFilePath(name);
    if(_set_path.find(file_path) != _set_path.end()){
        return;
    }

    QDir pro_dir(file_path);
    if(!pro_dir.exists()){
        bool enable = pro_dir.mkpath(file_path);
        if(!enable){
            return;
        }
    }

    _set_path.insert(file_path);
    auto* item = new ProTreeItem(this,name,file_path,TreeItemPro);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.png"));
    item->setData(0,Qt::ToolTipRole,file_path);
    this->addTopLevelItem(item);
}

void ProTreeWidget::SlotItemPressed(QTreeWidgetItem *pressedItem, int column)
{
    if(QGuiApplication::mouseButtons() == Qt::RightButton){
        QMenu menu(this);
        int itemtype = pressedItem->type();
        if(itemtype == TreeItemPro){
            _right_btn_item = pressedItem;//把这个item缓存了
            menu.addAction(_action_import);
            menu.addAction(_action_setstart);
            menu.addAction(_action_closepro);
            menu.addAction(_action_slideshow);
            menu.exec(QCursor::pos());
        }
    }
}

void ProTreeWidget::SlotDoubleClickItem(QTreeWidgetItem *doubleItem, int column)
{
    if(QGuiApplication::mouseButtons() == Qt::LeftButton){
        auto* tree_doubleItem = dynamic_cast<ProTreeItem*>(doubleItem);
        if(!tree_doubleItem){
            return;
        }

        int itemType = tree_doubleItem->type();
        if(itemType == TreeItemPic){
            emit SigUpdateSelected(tree_doubleItem->GetPath());
            _selected_item = doubleItem;
        }
    }
}

void ProTreeWidget::SlotImport()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    QString path;
    if(!_right_btn_item){
        qDebug()<<" _right_btn_item is empty "<<Qt::endl;
        return;
    }

    path = dynamic_cast<ProTreeItem*>(_right_btn_item)->GetPath();
    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;//缓存打开文件的结果
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }

    if(fileNames.length() <= 0){
        return;
    }

    QString import_path = fileNames.at(0);
    int file_count = 0;
    _dialog_progress = new QProgressDialog(this);

    //注：作为线程的参数来传递的时候，都是按照右值来构造的，而我们构造函数中都是引用
    //   所以这里要用 std::ref() 模拟引用传递的效果
    _thread_create_pro = std::make_shared<ProTreeThread>(std::ref(import_path),std::ref(path),_right_btn_item,
                                                         file_count,this,_right_btn_item,nullptr);

    connect(_thread_create_pro.get(),&ProTreeThread::SigUpdateProgress,this,&ProTreeWidget::SlotUpdateProgress);
    connect(_thread_create_pro.get(),&ProTreeThread::SigFinishProgress,this,&ProTreeWidget::SlotFinishProgress);
    connect(_dialog_progress,&QProgressDialog::canceled,this,&ProTreeWidget::SlotCancelProgress);
    connect(this,&ProTreeWidget::SigCancelProgress,_thread_create_pro.get(),&ProTreeThread::SlotCancelProgress);

    _thread_create_pro->start();

    _dialog_progress->setWindowTitle("Please wait...");
    _dialog_progress->setFixedWidth(PROGRESS_WIDTH);
    _dialog_progress->setRange(0,PROGRESS_WIDTH);
    _dialog_progress->exec();
}

void ProTreeWidget::SlotSetActive()
{
    if(!_right_btn_item){
        return;
    }

    QFont nullFont;
    nullFont.setBold(false);

    if(_active_item){
        _active_item->setFont(0,nullFont);
    }

    _active_item = _right_btn_item;
    nullFont.setBold(true);
    _active_item->setFont(0,nullFont);
}

void ProTreeWidget::SlotClosePro()
{
    RemoveProDialog remove_pro_dialog;
    auto ret = remove_pro_dialog.exec();
    if(ret != QDialog::Accepted){
        return;
    }

    bool b_remove = remove_pro_dialog.isRemoved();
    auto index_right_btn = this->indexOfTopLevelItem(_right_btn_item);
    auto* protreeitem = dynamic_cast<ProTreeItem*>(_right_btn_item);
    auto* selecteditem = dynamic_cast<ProTreeItem*>(_selected_item);
    auto delete_path = protreeitem->GetPath();
    _set_path.remove(delete_path);

    if(b_remove){
        QDir delete_dir(delete_path);
        delete_dir.removeRecursively();//递归地删除文件
    }

    if(protreeitem == _active_item){
        _active_item = nullptr;
    }

    if(selecteditem && protreeitem == selecteditem->GetRoot()){
        selecteditem = nullptr;
        _selected_item = nullptr;
        emit SigClearSelected();
    }

    delete this->takeTopLevelItem(index_right_btn);
    _right_btn_item = nullptr;
}

void ProTreeWidget::SlotSlideShow()
{
    if(!_right_btn_item){
        return;
    }

    auto* right_pro_item = dynamic_cast<ProTreeItem*>(_right_btn_item);
    auto* last_child_item = right_pro_item->GetLastPicChild();
    if(!last_child_item) return;
    auto* first_child_item = right_pro_item->GetFirstPicChild();
    if(!first_child_item) return;
    qDebug()<<" first_child_item is "<<first_child_item->GetPath();
    qDebug()<<" last_child_item is"<<last_child_item->GetPath();
    _slide_show_dlg = std::make_shared<SlideShowDlg>(first_child_item,last_child_item,this);
    _slide_show_dlg->setModal(true);
    _slide_show_dlg->showMaximized();
}

void ProTreeWidget::SlotUpdateProgress(int count)
{
    if(!_dialog_progress){
        return;
    }

    if(count >= PROGRESS_MAX){
        _dialog_progress->setValue(count%PROGRESS_MAX);
    }else{
        _dialog_progress->setValue(count);
    }
}

void ProTreeWidget::SlotFinishProgress()
{
    _dialog_progress->setValue(PROGRESS_MAX);
    _dialog_progress->deleteLater();
}

void ProTreeWidget::SlotCancelProgress()
{
    emit SigCancelProgress();
    delete _dialog_progress;
    _dialog_progress = nullptr;
}

void ProTreeWidget::SlotUpdateOpenProgress(int count)
{
    if(!_open_progressdlg){
        return;
    }

    if(count >= PROGRESS_MAX){
        _open_progressdlg->setValue(count%PROGRESS_MAX);
    }else{
        _open_progressdlg->setValue(count);
    }
}

void ProTreeWidget::SlotFinishOpenProgress()
{
    if(!_open_progressdlg){
        return;
    }

    _open_progressdlg->setValue(PROGRESS_MAX);
    delete _open_progressdlg;
    _open_progressdlg = nullptr;
}

void ProTreeWidget::SlotCancelOpenProgress()
{
    emit SigCancelOpenProgress();
    delete _open_progressdlg;
    _open_progressdlg = nullptr;
}

void ProTreeWidget::SlotOpenPro(const QString &path)
{
    if(_set_path.find(path) != _set_path.end()){
        return;
    }

    _set_path.insert(path);
    int file_count = 0;
    QDir pro_dir(path);
    QString proname = pro_dir.dirName();

    _thread_open_pro = std::make_shared<OpenTreeThread>(path,file_count,this,nullptr);

    _open_progressdlg = new QProgressDialog(this);
    connect(_thread_open_pro.get(),&OpenTreeThread::SigUpdateProgress,this,&ProTreeWidget::SlotUpdateOpenProgress);
    connect(_thread_open_pro.get(),&OpenTreeThread::SigFinishProgress,this,&ProTreeWidget::SlotFinishOpenProgress);
    connect(_open_progressdlg,&QProgressDialog::canceled,this,&ProTreeWidget::SlotCancelOpenProgress);
    connect(this,&ProTreeWidget::SigCancelOpenProgress,_thread_open_pro.get(),&OpenTreeThread::SlotCancelProgress);

    _thread_open_pro->start();

    _open_progressdlg->setWindowTitle("Please wait...");
    _open_progressdlg->setFixedWidth(PROGRESS_WIDTH);
    _open_progressdlg->setRange(0,PROGRESS_WIDTH);
    _open_progressdlg->exec();
}

void ProTreeWidget::SlotNextShow()
{
    if(!_selected_item){
        return;
    }

    auto* curItem = dynamic_cast<ProTreeItem*>(_selected_item)->GetNextItem();
    if(!curItem){
        return;
    }

    emit SigUpdatePic(curItem->GetPath());
    _selected_item = curItem;
    this->setCurrentItem(curItem);//设置curItem为激活状态
}

void ProTreeWidget::SlotPreShow()
{
    if(!_selected_item){
        return;
    }

    auto* curItem = dynamic_cast<ProTreeItem*>(_selected_item)->GetPreItem();
    if(!curItem){
        return;
    }

    emit SigUpdatePic(curItem->GetPath());
    _selected_item = curItem;
    this->setCurrentItem(curItem);
}

void ProTreeWidget::SlotSetMusic()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::ExistingFiles);
    file_dialog.setWindowTitle(tr("选择音频文件"));
    file_dialog.setDirectory(QDir::currentPath());
    file_dialog.setViewMode(QFileDialog::Detail);
    file_dialog.setNameFilter("(*.mp3)");
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }else{
        return;
    }

    if(fileNames.length()<=0) return;

    //初始化三件套
    _player = new QMediaPlayer(this);
    _audioOutput = new QAudioOutput(this);
    _playlist = new PlaylistController(this);

    _audioOutput->setVolume(0.15);
    _player->setAudioOutput(_audioOutput);
    _playlist->setPlayer(_player);

    for(auto&fileName:fileNames){
        _playlist->addMedia(QUrl::fromLocalFile(fileName));
    }

    if(_player->playbackState() != QMediaPlayer::PlayingState){
        _playlist->setCurrentIndex(0);
    }
}

void ProTreeWidget::SlotStartMusic()
{
    if(_player)
        _player->play();
}

void ProTreeWidget::SlotStopMusic()
{
    if(_player)
        _player->stop();
}
