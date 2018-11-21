#ifndef CHATITEMMSGTEXT_H
#define CHATITEMMSGTEXT_H

#include "ChatItemMsg.h"

class ChatItemMsgText : public ChatItemMsg
{
    Q_OBJECT
public:
    ChatItemMsgText(QWidget *parent = nullptr);

    ~ChatItemMsgText();

    QSize getRealString(QString src);

    QSize fontRect(QString src);
protected:
    void paintContent(QPainter& painter,const QRect& textRect);

};

#endif // CHATITEMMSGTEXT_H
