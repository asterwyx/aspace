#include "battery.h"
#include <QBrush>
#include <QPen>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

namespace dspace {
Battery::Battery(QWidget *parent)
    : QWidget(parent),
    m_timer(new QTimer(this))
{
    m_timer->setInterval(2);
    connect(m_timer, &QTimer::timeout, this, &Battery::updateValue);
    m_timer->start();
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
    painter->setBrush(QBrush(batteryGradient));
    painter->setPen(Qt::NoPen);
    int margin = qMin(width(), height()) / 20;
    double unit = (m_batteryRect.width() - (margin * 2)) / 100;
    double width = m_currentValue * unit;
    QPointF topLeft(m_batteryRect.topLeft().x() + margin, m_batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + 5, m_batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);
    painter->drawRoundedRect(rect, bgRadius, bgRadius);
    painter->restore();
}

void Battery::drawHead(QPainter *painter)
{
    painter->save();
    QPointF headRectTopLeft(m_batteryRect.topRight().x(), height() / 3.0);
    QPointF headRectBottomRight(width(), height() - height() / 3.0);
    QRectF  headRect(headRectTopLeft, headRectBottomRight);

    QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
    headRectGradient.setColorAt(0.0, borderColorStart);
    headRectGradient.setColorAt(1.0, borderColorEnd);
    painter->setBrush(QBrush(headRectGradient));
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(headRect, borderRadius, borderRadius);
    painter->restore();
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
    if (m_currentValue <= value) {
        m_currentValue += step;
        this->update();
    }
}

}