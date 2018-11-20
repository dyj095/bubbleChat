#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_send, SIGNAL(clicked(bool)), this, SLOT(onBtnSendClicked()));
    connect(ui->btn_sendImg, SIGNAL(clicked(bool)), this, SLOT(onBtnSendImgClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnSendClicked()
{
    QString message = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    // 发送中
    bool isSending = true;
    if (ui->listWidget->count() % 2) {
        if (isSending) {
            displayTime(time);

            ChatItemMsgText* messageW = new ChatItemMsgText(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            displayMessage(messageW, item, message, time, MessageUtil::Bubble_Me);
        }else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                ChatItemMsgText* messageW = (ChatItemMsgText*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->message() == message) {
                    isOver = false;
                    messageW->setSuccess();
                }
            }
            if(isOver) {
                displayTime(time);

                ChatItemMsgText* messageW = new ChatItemMsgText(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                displayMessage(messageW, item, message, time, MessageUtil::Bubble_Me);
                messageW->setSuccess();
            }
        }
    } else {
        if(message != "") {
            displayTime(time);

            ChatItemMsgText* messageW = new ChatItemMsgText(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            displayMessage(messageW, item, message, time, MessageUtil::Bubble_She);
        }
    }
}

void MainWindow::onBtnSendImgClicked()
{
    QString message = "";
    QFileDialog *fileDialog = new QFileDialog(this);//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
    fileDialog->setWindowTitle(tr("Save As"));//设置文件保存对话框的标题
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);//设置文件对话框为保存模式
    fileDialog->setFileMode(QFileDialog::AnyFile);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
    fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；

                                                                      //还有另一种形式QFileDialog::List，这个只是把文件的文件名以列表的形式显示出来
    fileDialog->setGeometry(10,30,300,200);//设置文件对话框的显示位置
    fileDialog->setDirectory(".");//设置文件对话框打开时初始打开的位置
    fileDialog->setNameFilter(tr("Image Files(*.jpg *.png)"));//设置文件类型过滤器
    if(fileDialog->exec() == QDialog::Accepted) {//注意使用的是QFileDialog::Accepted或者QDialog::Accepted,不是QFileDialog::Accept
        message = fileDialog->selectedFiles()[0];//得到用户选择的文件名
    }
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    // 发送中
    bool isSending = true;
    if (ui->listWidget->count() % 2) {
        if (isSending) {
            displayTime(time);

            ChatItemMsgImg* messageW = new ChatItemMsgImg(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            displayMessageForImg(messageW, item, message, time, MessageUtil::Bubble_Me);
        }else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                ChatItemMsgImg* messageW = (ChatItemMsgImg*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->message() == message) {
                    isOver = false;
                    messageW->setSuccess();
                }
            }
            if(isOver) {
                displayTime(time);

                ChatItemMsgImg* messageW = new ChatItemMsgImg(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                displayMessageForImg(messageW, item, message, time, MessageUtil::Bubble_Me);
                messageW->setSuccess();
            }
        }
    } else {
        if(message != "") {
            displayTime(time);

            ChatItemMsgImg* messageW = new ChatItemMsgImg(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            displayMessageForImg(messageW, item, message, time, MessageUtil::Bubble_She);
        }
    }
}

void MainWindow::displayTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        int lastTime = 0;
        QWidget *tempWidget = ui->listWidget->itemWidget(lastItem);
        ChatItemMsgText* messageW = dynamic_cast<ChatItemMsgText*>(tempWidget);
        if (messageW) {
            lastTime = messageW->time().toInt();
        } else {
            ChatItemMsgImg* messageImg = dynamic_cast<ChatItemMsgImg*>(tempWidget);
            if (messageImg) {
                lastTime = messageImg->time().toInt();
            }
        }

        //int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        ChatItemMsgText* messageTime = new ChatItemMsgText(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setMessage(curMsgTime, curMsgTime, size, MessageUtil::Bubble_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void MainWindow::displayMessage(ChatItemMsgText *messageW, QListWidgetItem *item, QString text, QString time, MessageUtil::Bubble_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setMessage(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void MainWindow::displayMessageForImg(ChatItemMsgImg *messageW, QListWidgetItem *item, QString text, QString time, MessageUtil::Bubble_Type type)
{
    messageW->setFixedWidth(this->width());
    messageW->setMaximumHeight(ui->listWidget->height());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setMessage(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}


void MainWindow::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);


    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->btn_send->move(ui->textEdit->width()+ui->textEdit->x() - ui->btn_send->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y() - ui->btn_send->height() - 10);


    for(int i = 0; i < ui->listWidget->count(); i++) {
        QWidget *tempWidget = ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);
        ChatItemMsgText* messageW = dynamic_cast<ChatItemMsgText*>(tempWidget);
        if (messageW) {
            displayMessage(messageW, item, messageW->message(), messageW->time(), messageW->bubbleType());
        } else {
            ChatItemMsgImg* messageImg = dynamic_cast<ChatItemMsgImg*>(tempWidget);
            if (messageImg) {
                displayMessageForImg(messageImg, item, messageImg->message(), messageImg->time(), messageImg->bubbleType());
            }
        }

    }
}
