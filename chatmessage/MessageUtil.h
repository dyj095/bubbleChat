#ifndef MESSAGEUTIL_H
#define MESSAGEUTIL_H

#include <QObject>

class MessageUtil : public QObject
{
    Q_OBJECT
public:
    explicit MessageUtil(QObject *parent = nullptr);

    enum Bubble_Type{
        Bubble_System,//系统
        Bubble_Me,    //自己
        Bubble_She,   //用户
        Bubble_Time,  //时间
    };

};

#endif // MESSAGEUTIL_H
