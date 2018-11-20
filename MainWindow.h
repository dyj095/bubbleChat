#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "chatItemMsgText/ChatItemMsgText.h"
#include "chatItemMsgImg/ChatItemMsgImg.h"
#include "chatItemMsgFile/ChatItemMsgFile.h"
#include "MessageUtil.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onBtnSendClicked();
    void onBtnSendImgClicked();
    void onBtnSendFileClicked();

private:
    void displayTime(QString curMsgTime);
    void displayMessage(ChatItemMsgText *messageW, QListWidgetItem *item, QString text, QString time, MessageUtil::Bubble_Type type);
    void displayMessageForImg(ChatItemMsgImg *messageW, QListWidgetItem *item, QString text, QString time, MessageUtil::Bubble_Type type);
    void displayMessageForFile(ChatItemMsgFile *messageW, QListWidgetItem *item, QString text, QString time, MessageUtil::Bubble_Type type);

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
