#include "CommonUtils.h"

#include <QPainter>
#include <QImage>
#include <QSize>

CommonUtils::CommonUtils()
{

}

CommonUtils::~CommonUtils(){

}

QPixmap CommonUtils::getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize)
{
    if (masksize.isNull()) {
        masksize = QSize(0, 0);
    }
    if (masksize == QSize(0, 0))
    {
        masksize = mask.size();
    }
    else
    {
        mask = mask.scaled(masksize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    QImage resultImage(masksize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, src.scaled(masksize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter.end();
    return QPixmap::fromImage(resultImage);
}
