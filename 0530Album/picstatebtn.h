#ifndef PICSTATEBTN_H
#define PICSTATEBTN_H

#include <QPushButton>

class PicStateBtn : public QPushButton
{
public:
    PicStateBtn(QWidget* parent = nullptr);
    void SetIcons(const QString& normal_o,const QString& hover_o, const QString& pressed_o,
                  const QString& normal_c,const QString& hover_c,const QString& pressed_c);

protected:
    bool event(QEvent* event) override;

private:
    void setNormalIcon_o();
    void setHoverIcon_o();
    void setPressIcon_o();

    void setNormalIcon_c();
    void setHoverIcon_c();
    void setPressIcon_c();

    QString _normal_o;
    QString _hover_o;
    QString _pressed_o;
    QString _normal_c;
    QString _hover_c;
    QString _pressed_c;
    int _cur_state;

public slots:
    void SlotStart();
    void SlotStop();
};

#endif // PICSTATEBTN_H
