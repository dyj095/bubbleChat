#include "ChatItemMsgImg.h"

ChatItemMsgImg::ChatItemMsgImg(QWidget *parent) : ChatItemMsg(parent)
{
    m_lineHeight = 20;
}

ChatItemMsgImg::~ChatItemMsgImg()
{

}

QSize ChatItemMsgImg::getRealString(QString src)
{
    int nMaxWidth = 0;
    int nCount = 0;
    int height = 0;
    if (!pixmap.isNull()) {
        QSize size = pixmap.size();
        nCount = size.height() / m_lineHeight;
        nMaxWidth = size.width();
        height = size.height();
        if (size.width() >= size.height()) {
            // 横
            if (size.width() > maxW) {
                QPixmap tmp = pixmap.scaledToWidth(maxW);
                if (tmp.height() > maxH) {
                    QPixmap tmp1 = tmp.scaledToHeight(maxH);
                    nMaxWidth = tmp1.width();
                    nCount = maxH / m_lineHeight;                    
                    height = tmp1.height();
                } else {
                    nMaxWidth = maxW;
                    nCount = tmp.height() / m_lineHeight;
                    height = tmp.height();
                }
            } else if (size.height() > maxH) {
                QPixmap tmp1 = pixmap.scaledToHeight(maxH);
                nMaxWidth = tmp1.width();
                nCount = maxH / m_lineHeight;                
                height = tmp1.height();
            }
        } else {
            // 竖
            if (size.height() > maxH) {
                QPixmap tmp = pixmap.scaledToHeight(maxH);
                if (tmp.width() > maxW) {
                    QPixmap tmp1 = tmp.scaledToWidth(maxW);
                    nMaxWidth = maxW;
                    nCount = tmp1.height() / m_lineHeight;                    
                    height = tmp1.height();
                } else {
                    nMaxWidth = tmp.width();
                    nCount = maxH / m_lineHeight;
                    height = tmp.height();
                }
            } else if (size.width() > maxW) {
                QPixmap tmp1 = pixmap.scaledToWidth(maxW);
                nMaxWidth = maxW;
                nCount = tmp1.height() / m_lineHeight;
                height = tmp1.height();
            }
        }
    }
    //return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2*m_lineHeight);
    return QSize(nMaxWidth, height + 2*m_lineHeight);
}

QSize ChatItemMsgImg::fontRect(QString src)
{
    m_msg = src;
    if (m_msg != NULL && m_msg.length() > 0) {
        bool isSuccess = pixmap.load(m_msg);
        qDebug() << "load picture:" << isSuccess << m_msg;
    }

    if (pixmap.isNull()) {
        pixmap.load(QString("D:/Qt/workspace/project/bubbleChat/imgs/pic/defaultPic.png"));
    }    

    maxW = this->width() * 0.59;
    maxH = this->maximumHeight() * 0.59;

    qDebug() << "this.width:" << this->width() << "    maxW:" << maxW;
    qDebug() << "this.height:" << this->maximumHeight() << "    maxH:" << maxH;

    m_kuangWidth = this->width() - kuangTMP - 2*(iconWH + iconSpaceW + iconRectW);
    m_textWidth = m_kuangWidth - 2* textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    // 左头像Rect
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    // 右头像Rect
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(src);

    int hei = size.height() < minHei ? minHei : size.height();
    qDebug() << "w:" << size.width() << " h:" << size.height();

    m_sanjiaoLeftRect = QRect(iconWH + iconSpaceW + iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if (size.width() < (m_textWidth)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(),
                                m_lineHeight/4*3,
                                size.width() + 2*textSpaceRect,
                                hei - m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3,
                                 size.width() + 2*textSpaceRect,
                                 hei - m_lineHeight);
    } else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(),
                                m_lineHeight/4*3,
                                m_kuangWidth,
                                hei - m_lineHeight);
        m_kuangRightRect.setRect(iconWH + iconSpaceW + iconRectW + kuangTMP - sanJiaoW,
                                 m_lineHeight/4*3,
                                 m_kuangWidth,
                                 hei-m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x() + textSpaceRect, m_kuangLeftRect.y() + iconTMPH,
                           m_kuangLeftRect.width() - 2*textSpaceRect, m_kuangLeftRect.height() - 2*iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x() + textSpaceRect,  m_kuangRightRect.y() + iconTMPH,
                            m_kuangRightRect.width() - 2*textSpaceRect, m_kuangRightRect.height() - 2*iconTMPH);
    return QSize(size.width(), hei);
}

void ChatItemMsgImg::paintContent(QPainter &painter, const QRect &textRect)
{
    // 内容
     painter.drawPixmap(textRect, pixmap);
}
