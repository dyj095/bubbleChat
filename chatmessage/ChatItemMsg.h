#ifndef CHATITEMMSG_H
#define CHATITEMMSG_H

#include <QWidget>
#include <QLabel>
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QSize>
#include <QDebug>

#include "MessageUtil.h"
#include "CommonUtils.h"

class ChatItemMsg : public QWidget
{
    Q_OBJECT
public:
    ChatItemMsg(QWidget *parent = nullptr);

    ~ChatItemMsg();

    void setSuccess();

    void setMessage(QString message, QString time, QSize allSize, MessageUtil::Bubble_Type bubbleType);

    virtual QSize getRealString(QString src){return QSize(0,0);}

    virtual QSize fontRect(QString src){return QSize(0,0);}


    inline QString message(){return m_msg;}
    inline QString time(){return m_time;}
    inline MessageUtil::Bubble_Type bubbleType(){return m_bubbleType;}

protected:
    void paintEvent(QPaintEvent *event);

    virtual void paintContent(QPainter& painter,const QRect& textRect){}

    void paintBubble();
protected:
    MessageUtil::Bubble_Type m_bubbleType = MessageUtil::Bubble_System;

    QString m_msg;
    QString m_time;
    QString m_curTime;

    QSize m_allSize;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight = 18;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;
    QLabel* m_loading = Q_NULLPTR;
    QMovie* m_loadingMovie = Q_NULLPTR;
    bool m_isSending = false;

    int minHei = 30;
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;

};

#endif // CHATITEMMSG_H
