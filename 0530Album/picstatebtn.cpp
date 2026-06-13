#include "picstatebtn.h"
#include "const.h"
#include "qcoreevent.h"

PicStateBtn::PicStateBtn(QWidget *parent)
    : QPushButton(parent)
{

}

void PicStateBtn::SetIcons(const QString &normal_o, const QString &hover_o, const QString &pressed_o, const QString &normal_c, const QString &hover_c, const QString &pressed_c)
{
    _normal_o = normal_o;
    _hover_o = hover_o;
    _pressed_o = pressed_o;

    _normal_c = normal_c;
    _hover_c = hover_c;
    _pressed_c = pressed_c;

    QPixmap tmpPixmap;
    tmpPixmap.load(normal_o);
    this->resize(tmpPixmap.size());
    this->setIcon(tmpPixmap);
    this->setIconSize(tmpPixmap.size());
    _cur_state = PicBtnStateNormal_o;
}

bool PicStateBtn::event(QEvent *event)
{
    switch(event->type()){
    case QEvent::Enter:
        if(_cur_state < PicBtnStateNormal_c){
            setHoverIcon_o();
        }else{
            setHoverIcon_c();
        }
        break;

    case QEvent::Leave:
        if(_cur_state < PicBtnStateNormal_c){
            setNormalIcon_o();
        }else{
            setNormalIcon_c();
        }
        break;

    case QEvent::MouseButtonPress:
        if(_cur_state < PicBtnStateNormal_c){
            setPressIcon_o();
        }else{
            setPressIcon_c();
        }
        break;

    case QEvent::MouseButtonRelease:
        if(_cur_state < PicBtnStateNormal_c){
            setHoverIcon_c();
        }else{
            setHoverIcon_o();
        }
        break;

    default:
        break;
    }

    return QPushButton::event(event);
}

void PicStateBtn::setNormalIcon_o()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal_o);
    this->setIcon(tmpPixmap);
    _cur_state = PicBtnStateNormal_o;
}

void PicStateBtn::setHoverIcon_o()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover_o);
    this->setIcon(tmpPixmap);
    _cur_state = PicBtnStateHover_o;
}

void PicStateBtn::setPressIcon_o()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed_o);
    this->setIcon(tmpPixmap);
    _cur_state = PicBtnStatePress_o;
}

void PicStateBtn::setNormalIcon_c()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal_c);
    this->setIcon(tmpPixmap);
    _cur_state = PicBtnStateNormal_c;
}

void PicStateBtn::setHoverIcon_c()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover_c);
    this->setIcon(tmpPixmap);
    _cur_state = PicBtnStateHover_c;
}

void PicStateBtn::setPressIcon_c()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed_c);
    this->setIcon(tmpPixmap);
    _cur_state = PicBtnStatePress_c;
}

void PicStateBtn::SlotStart()
{
    setNormalIcon_c();
}

void PicStateBtn::SlotStop()
{
    setNormalIcon_o();
}

