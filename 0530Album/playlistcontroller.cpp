#include "playlistcontroller.h"

PlaylistController::PlaylistController(QObject *parent)
    : QObject{parent}
{}

void PlaylistController::setPlayer(QMediaPlayer *player)
{
    m_player = player;
    // 监听播放器状态，当一首歌播放结束时，自动下一首
    connect(m_player,&QMediaPlayer::mediaStatusChanged,this,&PlaylistController::SlotMediaStatusChanged);
}

void PlaylistController::addMedia(const QUrl &url)
{
    m_playlist.append(url);
    if(m_playlist.size() == 1){
        setCurrentIndex(0);
    }
}

void PlaylistController::clear()
{
    m_playlist.clear();
    setCurrentIndex(-1);
}

void PlaylistController::next()
{
    if(m_playlist.empty()) return;

    if(m_curIdx < m_playlist.size() - 1){
        setCurrentIndex(m_curIdx+1);
    }else{
        setCurrentIndex(0);//到达末尾回到开头 -> 循环
    }
}

void PlaylistController::previous()
{
    if(m_playlist.empty()) return;

    if(m_curIdx > 0){
        setCurrentIndex(m_curIdx-1);
    }else{
        setCurrentIndex(m_playlist.size()-1);//到达开头来到末尾 -> 循环
    }
}

int PlaylistController::currentIndex() const
{
    return m_curIdx;
}

void PlaylistController::setCurrentIndex(int index)
{
    if(index == m_curIdx || index < 0 || index >= m_playlist.size()) return;

    m_curIdx = index;

    if(m_player){
        m_player->setSource(currentUrl());//改变索引时，将新的 URL 设置给播放器
    }
}

QUrl PlaylistController::currentUrl() const
{
    if(m_curIdx>=0 && m_curIdx < m_playlist.size()){
        return m_playlist.at(m_curIdx);
    }

    return QUrl();
}

void PlaylistController::SlotMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    // 当媒体播放到结尾时，自动切换下一首
    if(status == QMediaPlayer::EndOfMedia){
        next();
    }
}
