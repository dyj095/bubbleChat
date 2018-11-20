#include "ChatItemMsgImg.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QDebug>

ChatItemMsgImg::ChatItemMsgImg(QWidget *parent) : QWidget(parent)
{
    QString leftHeadFilePath = QString("D:/Qt/workspace/project/bubbleChat/imgs/pic/2.jpg");
    QPixmap leftPixmap;
    leftPixmap.load(leftHeadFilePath);
    QPixmap maskPixmap;
    maskPixmap.load(":/chatmessage/Resources/img/head_mask.png");
    m_leftPixmap = CommonUtils::getRoundImage(leftPixmap, maskPixmap, QSize(40,40));

    QString rightHeadFilePath = QString("D:/Qt/workspace/project/bubbleChat/imgs/pic/3.jpg");
    QPixmap rightPixmap;
    rightPixmap.load(rightHeadFilePath);
    m_rightPixmap = CommonUtils::getRoundImage(rightPixmap, maskPixmap, QSize(40,40));;

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/chatmessage/Resources/img/loading.gif");
    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16,16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground , true);
    m_loading->setAutoFillBackground(false);

    m_lineHeight = 18;
}

void ChatItemMsgImg::setSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void ChatItemMsgImg::setMessage(QString message, QString time, QSize allSize, MessageUtil::Bubble_Type bubbleType)
{
    m_msg = message;
    m_bubbleType = bubbleType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("hh:mm");
    m_allSize = allSize;
    if (bubbleType == MessageUtil::Bubble_Me) {
        if (!m_isSending) {
            m_loading->move(m_kuangRightRect.x() - m_loading->width() - 10, m_kuangRightRect.y() + m_kuangRightRect.height()/2-m_loading->height()/2);
            m_loading->show();
            m_loadingMovie->start();
        }
    } else {
        m_loading->hide();
    }
}

QSize ChatItemMsgImg::getRealString(QString src)
{
    int nMaxWidth = 0;
    int nCount = 0;
    if (!pixmap.isNull()) {
        QSize size = pixmap.size();
        nCount = size.height() / m_lineHeight;
        nMaxWidth = size.width();
        if (size.width() >= size.height()) {
            // 横
            if (size.width() > maxW) {
                QPixmap tmp = pixmap.scaledToWidth(maxW);
                if (tmp.height() > maxH) {
                    QPixmap tmp1 = tmp.scaledToHeight(maxH);
                    nMaxWidth = tmp1.width();
                    nCount = maxH / m_lineHeight;
                } else {
                    nMaxWidth = maxW;
                    nCount = tmp.height() / m_lineHeight;
                }
            } else if (size.height() > maxH) {
                QPixmap tmp1 = pixmap.scaledToHeight(maxH);
                nMaxWidth = tmp1.width();
                nCount = maxH / m_lineHeight;
            }
        } else {
            // 竖
            if (size.height() > maxH) {
                QPixmap tmp = pixmap.scaledToHeight(maxH);
                if (tmp.width() > maxW) {
                    QPixmap tmp1 = tmp.scaledToWidth(maxW);
                    nMaxWidth = maxW;
                    nCount = tmp1.height() / m_lineHeight;
                } else {
                    nMaxWidth = tmp.width();
                    nCount = maxH / m_lineHeight;
                }
            } else if (size.width() > maxW) {
                QPixmap tmp1 = pixmap.scaledToWidth(maxW);
                nMaxWidth = maxW;
                nCount = tmp1.height() / m_lineHeight;
            }
        }
    }
    return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2*m_lineHeight);
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

    m_sanjiaoLeftRect = QRect(iconWH + iconSpaceW + iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if (size.width() < (m_textWidth + m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(),
                                m_lineHeight/4*3,
                                size.width() - m_spaceWid + 2*textSpaceRect,
                                hei - m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3,
                                 size.width() - m_spaceWid + 2*textSpaceRect,
                                 hei - m_lineHeight);
    } else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei - m_lineHeight);
        m_kuangRightRect.setRect(iconWH + iconSpaceW + iconRectW + kuangTMP - sanJiaoW, m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x() + textSpaceRect, m_kuangLeftRect.y() + iconTMPH,
                           m_kuangLeftRect.width() - 2*textSpaceRect, m_kuangLeftRect.height() - 2*iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x() + textSpaceRect,  m_kuangRightRect.y() + iconTMPH,
                            m_kuangRightRect.width() - 2*textSpaceRect, m_kuangRightRect.height() - 2*iconTMPH);
    return QSize(size.width(), hei);
}

void ChatItemMsgImg::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // 消锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));
    if (m_bubbleType == MessageUtil::Bubble_She) {
        // 其她人
        // 1.头像
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        // 2.框
        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x() -1, m_kuangLeftRect.y() -1, m_kuangLeftRect.width() + 2, m_kuangLeftRect.height() +2,4, 4);
        //框
        QColor col_Kuang(255,255,255);
        //QColor col_Kuang(229,229,229);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect, 4, 4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoLeftRect.x(), 30),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 25),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        QPen panSanJiaoBian;
        panSanJiaoBian.setColor(col_KuangB);
        painter.setPen(panSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 36));

        // 内容
        painter.drawPixmap(m_textLeftRect, pixmap);
    } else if (m_bubbleType == MessageUtil::Bubble_Me) {
        // 自己发送的消息（右边）
        // 1.头像
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);
        // 2.框
        //框
        QColor col_Kuang(75,164,242);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect, 4, 4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoRightRect.x()+m_sanjiaoRightRect.width(), 30),
            QPointF(m_sanjiaoRightRect.x(), 25),
            QPointF(m_sanjiaoRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

       // 内容
        painter.drawPixmap(m_textRightRect, pixmap);
    } else if (m_bubbleType == MessageUtil::Bubble_Time) {
        QPen penText;
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("MicrosoftYaHei");
        te_font.setPointSize(10);
        painter.setFont(te_font);
        painter.drawText(this->rect(),m_curTime,option);
    }
}
