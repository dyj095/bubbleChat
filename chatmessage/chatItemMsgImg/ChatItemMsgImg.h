#ifndef CHATITEMMSGIMG_H
#define CHATITEMMSGIMG_H

#include "ChatItemMsg.h"

class ChatItemMsgImg : public ChatItemMsg
{
    Q_OBJECT
public:
    ChatItemMsgImg(QWidget *parent = nullptr);

    ~ChatItemMsgImg();

    QSize getRealString(QString src);

    QSize fontRect(QString src);
protected:
    void paintContent(QPainter& painter,const QRect& textRect);

private:
    // 当前图片
    QPixmap pixmap;
    int maxW;
    int maxH;
};

#endif // CHATITEMMSGIMG_H
