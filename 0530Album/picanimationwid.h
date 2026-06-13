#ifndef PICANIMATIONWID_H
#define PICANIMATIONWID_H

#include <QWidget>
#include <QTreeWidgetItem>

class PicAnimationWid : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimationWid(QWidget *parent = nullptr);
    ~PicAnimationWid();
    void SetPixmap(QTreeWidgetItem* item);
    void Start();
    void Stop();
    void SlideNext();
    void SlidePre();

protected:
    virtual void paintEvent(QPaintEvent* event);

private:
    float _factor;//当前图片播放状态
    QTimer* _timer;
    //这里用双缓冲
    QPixmap _pixmap1;//加载当前item
    QPixmap _pixmap2;//加载当前item的下一个item
    QTreeWidgetItem* _cur_item;
    QMap<QString,QTreeWidgetItem*> _map_items;
    bool _b_start;

    void UpSelectPixmap(QTreeWidgetItem* item);

private slots:
    void TimeOut();

public slots:
    void SlotUpSelectShow(QString& path);
    void SlotStartOrStop();

signals:
    void SigUpPreList(QTreeWidgetItem*);
    void SigSelectedItem(QTreeWidgetItem*);
    void SigStart();
    void SigStop();
    void SigStartMusic();
    void SigStopMusic();
};

#endif // PICANIMATIONWID_H
