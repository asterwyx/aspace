#include "battery.h"
#include <QBrush>
#include <QPen>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

namespace dspace {
Battery::Battery(QWidget *parent)
    : QWidget(parent),
    m_timer(new QTimer(this))
{

}

Battery::~Battery() = default;

void Battery::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    
    drawBorder(&painter);
    drawBg(&painter);
    drawHead(&painter);
    
}

void Battery::drawBorder(QPainter *painter)
{
    painter->save();
    
    double headWidth = static_cast<double>(width()) / 10;
    double batteryWidth = width() - headWidth;
    
    QPointF topLeft(5,5);
    QPointF bottomRight(batteryWidth, height() - 5);

    m_batteryRect = QRectF(topLeft, bottomRight);
    
    painter->setPen(QPen(borderColorStart, 5));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(m_batteryRect, borderRadius, borderRadius);

    painter->restore();
}

void Battery::drawBg(QPainter *painter)
{
    painter->save();

    QLinearGradient batteryGradient(QPointF(0,0), QPointF(0, height()));
    if (m_currentValue <= alarmValue)
    {
        batteryGradient.setColorAt(0.0, alarmColorStart);
        batteryGradient.setColorAt(1.0, alarmColorEnd);
    }
    else
    {
        batteryGradient.setColorAt(0.0, normalColorStart);
        batteryGradient.setColorAt(1.0, normalColorEnd);
    }
    int margin = qMin(width(), height()) / 20;
    Q_UNUSED(margin)

    painter->restore();
}

void Battery::drawHead(QPainter *painter)
{
    Q_UNUSED(painter)
}

QSize Battery::sizeHint()  const
{
    return QSize();
}
QSize Battery::minimumSizeHint() const
{
    return QSize();    
}


void Battery::updateValue()
{

}

}