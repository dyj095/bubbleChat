#ifndef CHATITEMMSGTEXT_H
#define CHATITEMMSGTEXT_H

#include <QWidget>
#include <QLabel>
#include "MessageUtil.h"
#include "CommonUtils.h"

class ChatItemMsgText : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemMsgText(QWidget *parent = nullptr);

    void setSuccess();

    void setMessage(QString message, QString time, QSize allSize, MessageUtil::Bubble_Type bubbleType);

    QSize getRealString(QString src);

    QSize fontRect(QString src);

    inline QString message(){return m_msg;}
    inline QString time(){return m_time;}
    inline MessageUtil::Bubble_Type bubbleType(){return m_bubbleType;}
protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_msg;
    QString m_time;
    QString m_curTime;

    QSize m_allSize;
    MessageUtil::Bubble_Type m_bubbleType = MessageUtil::Bubble_System;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

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

#endif // CHATITEMMSGTEXT_H
