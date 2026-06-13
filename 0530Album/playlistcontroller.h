#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QList>
#include <QUrl>

class PlaylistController : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistController(QObject *parent = nullptr);
    void setPlayer(QMediaPlayer* player);
    void addMedia(const QUrl& url);
    void clear();

    void next();
    void previous();

    int currentIndex() const;
    void setCurrentIndex(int index);

    QUrl currentUrl() const;

private slots:
    void SlotMediaStatusChanged(QMediaPlayer::MediaStatus status);

signals:

private:
    QMediaPlayer* m_player = nullptr;
    QList<QUrl> m_playlist;
    int m_curIdx = -1;
};

#endif // PLAYLISTCONTROLLER_H
