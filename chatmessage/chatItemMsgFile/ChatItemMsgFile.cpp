#include "ChatItemMsgFile.h"
#include "ui_ChatItemMsgFile.h"

ChatItemMsgFile::ChatItemMsgFile(QWidget *parent) :
    ChatItemMsg(parent),
    ui(new Ui::ChatItemMsgFile)
{
    ui->setupUi(this);
    progressBar = new QProgressBar(ui->topWidget);
    progressBar->setTextVisible(false);
    progressBar->setStyleSheet(QString("QProgressBar::chunk{background-color: rgb(11, 134, 210);}"));
    progressBar->setGeometry(QRect(ui->topWidget->x(), ui->topWidget->height() + 3, ui->topWidget->width(), 2));
    //progressBar->setValue(70);
    //progressBar->show();
    progressBar->hide();
    ui->fileWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->fileWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightClickMenu(QPoint)));
    connect(ui->btnMoreOption, SIGNAL(clicked(bool)), this, SLOT(onBtnMoreOptionClicked()));

    connect(ui->lbOpenFile, SIGNAL(linkActivated(QString)), this, SLOT(openFile(QString)));
    connect(ui->lbOpenFolder, SIGNAL(linkActivated(QString)), this, SLOT(openFolder(QString)));
    connect(ui->lbForward, SIGNAL(linkActivated(QString)), this, SLOT(forward(QString)));
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

void ChatItemMsgFile::paintContent(QPainter &painter, const QRect &textRect)
{
    //内容
    ui->fileWidget->setGeometry(textRect);
}

void ChatItemMsgFile::onBtnMoreOptionClicked()
{
    m_moreOptionMenu = new QMenu();

    // 如果要设置菜单右箭头图标使用：QMenu::right-arrow{ background: url(:/tiny/lb_arrow_up_normal);}
    const QString MenuStyle = " \
            QMenu{ padding:0px; padding-top:6px;padding-bottom:6px;border:1px solid #EDEDED; background:rgba(255, 255, 255, 210); border-radius:5px;} \
            QMenu::icon{ margin-left:38px;} \
            QMenu::item{ color:#171717; padding:6px 40px 6px 20px; border:1px solid transparent;} \
            QMenu::item:disabled{ color:#EEEEEE;} \
            QMenu::item:selected{ color:#171717; background:rgba(238, 238, 238, 200);} \
            QMenu::separator{ height:1px; background:#EDEDED; margin-top:5px; margin-bottom:5px;}";
    m_moreOptionMenu->setWindowFlags(m_moreOptionMenu->windowFlags() | Qt::FramelessWindowHint);
    m_moreOptionMenu->setAttribute(Qt::WA_TranslucentBackground);
    m_moreOptionMenu->setStyleSheet(MenuStyle);

    QAction *pActionOnline = m_moreOptionMenu->addAction(QString::fromLocal8Bit("存到云盘"));
    QAction *pActionBusy = m_moreOptionMenu->addAction(QString::fromLocal8Bit("打开文件助手"));
    // 设置状态值;

    connect(m_moreOptionMenu, SIGNAL(triggered(QAction *)), this, SLOT(onMenuClicked(QAction*)));


    QPoint pos = ui->btnMoreOption->mapToGlobal(QPoint(0, 0)) + QPoint(0, 20);
    m_moreOptionMenu->exec(pos);
}

void ChatItemMsgFile::onMenuClicked(QAction *action)
{
    qDebug() << "===================";
    progressBar->show();
    progressBar->setValue(100);
}

void ChatItemMsgFile::showRightClickMenu(const QPoint &pos)
{

    m_contextMenu = new QMenu();

    // 如果要设置菜单右箭头图标使用：QMenu::right-arrow{ background: url(:/tiny/lb_arrow_up_normal);}
    const QString MenuStyle = " \
            QMenu{ padding:0px; padding-top:6px;padding-bottom:6px;border:1px solid #EDEDED; background:rgba(255, 255, 255, 210); border-radius:5px;} \
            QMenu::icon{ margin-left:38px;} \
            QMenu::item{ color:#171717; padding:6px 40px 6px 20px; border:1px solid transparent;} \
            QMenu::item:disabled{ color:#EEEEEE;} \
            QMenu::item:selected{ color:#171717; background:rgba(238, 238, 238, 200);} \
            QMenu::separator{ height:1px; background:#EDEDED; margin-top:5px; margin-bottom:5px;}";
    m_contextMenu->setWindowFlags(m_contextMenu->windowFlags() | Qt::FramelessWindowHint);
    m_contextMenu->setAttribute(Qt::WA_TranslucentBackground);
    m_contextMenu->setStyleSheet(MenuStyle);

    QAction *pActionOnline = m_contextMenu->addAction(QString::fromLocal8Bit("下载"));
    QAction *pActionBusy = m_contextMenu->addAction(QString::fromLocal8Bit("另存为"));
    QAction *pActionForward = m_contextMenu->addAction(QString::fromLocal8Bit("转发"));
    QAction *pActionSaveToYunPan = m_contextMenu->addAction(QString::fromLocal8Bit("存到云盘"));
    QAction *pActionFileAsistant = m_contextMenu->addAction(QString::fromLocal8Bit("打开文件助手"));
    // 设置状态值;

    connect(m_contextMenu, SIGNAL(triggered(QAction *)), this, SLOT(onMenuClicked(QAction*)));

    QPoint pos1 = ui->fileWidget->mapToGlobal(QPoint(0, 0)) + pos;

    m_contextMenu->exec(pos1);
}

void ChatItemMsgFile::openFile(QString url)
{
    qDebug() << "openFile:" << url;
}

void ChatItemMsgFile::openFolder(QString url)
{
    qDebug() << "openFolder:" << url;
}

void ChatItemMsgFile::forward(QString url)
{
    qDebug() << "forward:" << url;
}
