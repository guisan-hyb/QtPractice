#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include <QAction>
#include <QProgressDialog>
#include "protreethread.h"
#include "opentreethread.h"

//QMediaPlayer 必须配合 QAudioOutput 才能发出声音
#include <QMediaPlayer>
#include <QAudioOutput>
#include "playlistcontroller.h"


class SlideShowDlg;//前向声明

class ProTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    ProTreeWidget(QWidget* parent = nullptr);
    void AddProToTree(const QString& name, const QString& path);
private:
    QSet<QString> _set_path;//用来判断是否重名
    QTreeWidgetItem* _right_btn_item;//右键单击某个item之后弹出菜单
    QTreeWidgetItem* _active_item;//记录当前启动的项目
    QTreeWidgetItem* _selected_item;//双击某个item
    QAction* _action_import;
    QAction* _action_setstart;
    QAction* _action_closepro;
    QAction* _action_slideshow;
    QProgressDialog* _dialog_progress;
    QProgressDialog* _open_progressdlg;
    std::shared_ptr<ProTreeThread> _thread_create_pro;
    std::shared_ptr<OpenTreeThread> _thread_open_pro;
    std::shared_ptr<SlideShowDlg> _slide_show_dlg;

    QMediaPlayer* _player;
    QAudioOutput* _audioOutput;
    PlaylistController* _playlist;


private slots:
    void SlotItemPressed(QTreeWidgetItem* item, int column);
    void SlotDoubleClickItem(QTreeWidgetItem* doubleItem, int column);
    void SlotImport();
    void SlotSetActive();
    void SlotClosePro();
    void SlotSlideShow();
    void SlotUpdateProgress(int count);
    void SlotFinishProgress();
    void SlotCancelProgress();

    void SlotUpdateOpenProgress(int count);
    void SlotFinishOpenProgress();
    void SlotCancelOpenProgress();

public slots:
    void SlotOpenPro(const QString& path);
    void SlotNextShow();
    void SlotPreShow();
    void SlotSetMusic();
    void SlotStartMusic();
    void SlotStopMusic();

signals:
    void SigCancelProgress();
    void SigCancelOpenProgress();
    void SigUpdateSelected(const QString&);
    void SigUpdatePic(const QString&);
    void SigClearSelected();
};

#endif // PROTREEWIDGET_H
