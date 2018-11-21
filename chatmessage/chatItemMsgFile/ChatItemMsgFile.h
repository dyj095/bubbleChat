#ifndef CHATITEMMSGFILE_H
#define CHATITEMMSGFILE_H

#include <QProgressBar>
#include <QTimer>
#include <QMenu>

#include "ChatItemMsg.h"

namespace Ui {
class ChatItemMsgFile;
}

class ChatItemMsgFile : public ChatItemMsg
{
    Q_OBJECT
public:
    ChatItemMsgFile(QWidget *parent = 0);
    ~ChatItemMsgFile();

    QSize getRealString(QString src);

    QSize fontRect(QString src);
protected:
    void paintContent(QPainter& painter,const QRect& textRect);

private slots:
    void onBtnMoreOptionClicked();

    // 用户状态菜单点击;
    void onMenuClicked(QAction * action);

    void showRightClickMenu(const QPoint &pos);

    void openFile(QString url);

    void openFolder(QString url);

    void forward(QString url);
private:
    Ui::ChatItemMsgFile *ui;
    QProgressBar *progressBar;
    QMenu *m_moreOptionMenu;
    QMenu *m_contextMenu;
};

#endif // CHATITEMMSGFILE_H
