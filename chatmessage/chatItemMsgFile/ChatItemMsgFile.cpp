#include "ChatItemMsgFile.h"
#include "ui_ChatItemMsgFile.h"

ChatItemMsgFile::ChatItemMsgFile(QWidget *parent) :
    ChatItemMsg(parent),
    ui(new Ui::ChatItemMsgFile)
{
    ui->setupUi(this);
    progressBar = new QProgressBar(ui->topWidget);
    progressBar->setTextVisible(false);
    progressBar->setGeometry(QRect(ui->topWidget->x(), ui->topWidget->height() + 3, ui->topWidget->width(), 2));
    progressBar->setValue(100);
    progressBar->show();
}

ChatItemMsgFile::~ChatItemMsgFile()
{
    delete progressBar;
    delete ui;
}

QSize ChatItemMsgFile::getRealString(QString src)
{
    int nMaxWidth = 295;
    int nCount = 100/m_lineHeight;
    return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2*m_lineHeight);
}

QSize ChatItemMsgFile::fontRect(QString src)
{
    m_msg = src;
    m_kuangWidth = this->width() - kuangTMP - 2 * (iconWH + iconSpaceW + iconRectW);
    m_textWidth = m_kuangWidth - 2 * textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg);
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    } else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x()+textSpaceRect,m_kuangLeftRect.y()+iconTMPH,
                           m_kuangLeftRect.width()-2*textSpaceRect,m_kuangLeftRect.height()-2*iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x()+textSpaceRect,m_kuangRightRect.y()+iconTMPH,
                            m_kuangRightRect.width()-2*textSpaceRect,m_kuangRightRect.height()-2*iconTMPH);

    return QSize(size.width(), hei);
}

void ChatItemMsgFile::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    paintBubble();
}

void ChatItemMsgFile::paintContent(QPainter &painter, const QRect &textRect)
{
    //内容
    ui->fileWidget->setGeometry(textRect);
}

