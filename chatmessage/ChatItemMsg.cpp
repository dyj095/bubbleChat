#include "ChatItemMsg.h"

ChatItemMsg::ChatItemMsg(QWidget *parent) : QWidget(parent)
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
}

ChatItemMsg::~ChatItemMsg()
{

}

void ChatItemMsg::setSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void ChatItemMsg::setMessage(QString message, QString time, QSize allSize, MessageUtil::Bubble_Type bubbleType){
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

void ChatItemMsg::paintBubble()
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));
    if (m_bubbleType == MessageUtil::Bubble_She) {
        // 其她人
        // 1.头像
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x()-1,m_kuangLeftRect.y()-1,m_kuangLeftRect.width()+2,m_kuangLeftRect.height()+2,4,4);
        //框
        QColor col_Kuang(255,255,255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect,4,4);

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

        //三角加边
        QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 36));

        //内容
        paintContent(painter, m_textLeftRect);
    } else if (m_bubbleType == MessageUtil::Bubble_Me) {
        // 自己发送的消息（右边）
        // 1.头像
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //框
        QColor col_Kuang(75,164,242);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect,4,4);

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
        //内容
        paintContent(painter, m_textRightRect);
    }  else if(m_bubbleType == MessageUtil::Bubble_Time) { // 时间
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
