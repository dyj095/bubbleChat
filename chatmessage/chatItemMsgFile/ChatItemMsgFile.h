#ifndef CHATITEMMSGFILE_H
#define CHATITEMMSGFILE_H

#include <QProgressBar>
#include <QTimer>

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
private:
    Ui::ChatItemMsgFile *ui;
    QProgressBar *progressBar;
};

#endif // CHATITEMMSGFILE_H
