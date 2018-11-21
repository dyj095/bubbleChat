#include "ChatItemMsgText.h"

ChatItemMsgText::ChatItemMsgText(QWidget *parent) : ChatItemMsg(parent)
{
    QFont te_font = this->font();
    te_font.setFamily("MicrosoftYaHei");
    te_font.setPointSize(12);
    //    te_font.setWordSpacing(0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing,0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing, 100);          //300%,100为默认  //设置字间距%
    //    te_font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             //设置字间距为3像素 //设置字间距像素值
    this->setFont(te_font);
}

ChatItemMsgText::~ChatItemMsgText()
{

}

QSize ChatItemMsgText::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    // 文字内容显示行数
    int nCount = 0;
    // 每行显示的最大宽度
    int nMaxWidth = 0;
    qDebug() << "src:" << src;
    if (src != NULL && src.length() > 0) {
        nCount = src.count("\n");
        if (nCount == 0) {
            nMaxWidth = fm.width(src);
            QString value = src;
            if (nMaxWidth > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                //int ttmp = num * fm.width(" ");
                num = (fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for (int i = 0; i < num ; i++) {
                    temp += value.mid(i * size, (i + 1) * size) + "\n";
                }
                src.replace(value, temp);
            }
        } else {
            int length = (nCount + 1);
            for(int i = 0; i < length; i++) {
                // 第i行消息内容
                QString value = src.split("\n").at(i);
                nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
                if (fm.width(value) > m_textWidth) {
                    nMaxWidth = m_textWidth;
                    // 气泡中1行可以显示的字符数
                    int size = m_textWidth / fm.width(" ");
                    // 内容是否可以在1行内显示
                    int num = fm.width(value) / m_textWidth;
                    num = ((i + num) * fm.width(" ") + fm.width(value)) / m_textWidth;
                    nCount += num;
                    QString temp = "";
                    for (int j = 0; j < num; j++) {
                        temp += value.mid(j * size, (j + 1) * size) + "\n";
                    }
                    src.replace(value, temp);
                }
            }
        }
    }
    return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2 * m_lineHeight);
}

QSize ChatItemMsgText::fontRect(QString src)
{
    m_msg = src;
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
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width() - m_spaceWid + 2*textSpaceRect, hei - m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3, size.width() - m_spaceWid + 2*textSpaceRect, hei - m_lineHeight);
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

void ChatItemMsgText::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paintBubble();
}

void ChatItemMsgText::paintContent(QPainter& painter, const QRect& textRect){
    // 内容
    QPen penText;
    if (textRect == m_textLeftRect) {
        penText.setColor(QColor(51,51,51));
    } else {
        penText.setColor(Qt::white);
    }
    painter.setPen(penText);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    painter.setFont(this->font());
    painter.drawText(textRect, m_msg,option);
}
