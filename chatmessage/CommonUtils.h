#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QPixmap>

class CommonUtils
{
public:
    CommonUtils();
    ~CommonUtils();
    static QPixmap getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize);
};

#endif // COMMONUTILS_H
