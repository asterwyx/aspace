#include "weathericon.h"
#include "weathericon_p.h"
#include <QSvgRenderer>
#include <QSvgWidget>
#include <QPainter>
#include <QDomDocument>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include "utils.h"

BEGIN_USER_NAMESPACE
WeatherIcon::WeatherIcon(const QString& iconPath, double scaleFactor, IconType type, QWidget *parent)
    : QWidget{parent}, d_ptr{new WeatherIconPrivate(this)}
{
    Q_D(WeatherIcon);
    d->m_scaleFactor = scaleFactor;
    d->m_iconPath = iconPath;
    d->m_iconType = type;
    if (type == SVG)
    {
        QFile iconFile(d->m_iconPath);
        iconFile.open(QIODevice::ReadOnly);
        d->m_svgData = iconFile.readAll();
        iconFile.close();
    }
}

void WeatherIcon::setSvgColor(QColor color)
{
    Q_D(WeatherIcon);
    if (d->m_iconType == PNG)
    {
        qWarning() << "Icon type is PNG, cannot set color.";
        return;
    }
    QDomDocument doc;
    doc.setContent(d->m_svgData);
    int red, green, blue;
    color.getRgb(&red, &green, &blue);
    QString colorString =QString::asprintf("rgb(%d,%d,%d)", red, green, blue);
    auto elem = doc.documentElement();
    elem = Utils::setXmlAttrValueRecurse(doc.documentElement(), "fill", colorString);
    doc.replaceChild(doc.documentElement(), elem);
    d->m_svgData = doc.toByteArray();
}

void WeatherIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(WeatherIcon);
    if (d->m_iconType == SVG) {
        QSvgRenderer renderer;
        renderer.load(d->m_svgData);
        auto size = renderer.defaultSize();
        QPixmap pixmap(size * d->m_scaleFactor);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing);
        renderer.render(&painter);
        painter.end();
        painter.begin(this);
        painter.drawPixmap(0, 0, pixmap);
    } else {
        QPixmap pixmap(d->m_iconPath);
        pixmap.scaled(pixmap.size() * d->m_scaleFactor);
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap);
    }
}

WeatherIcon::~WeatherIcon() = default;

WeatherIconPrivate::WeatherIconPrivate(WeatherIcon *q) : q_ptr(q) {}
WeatherIconPrivate::~WeatherIconPrivate() = default;
END_USER_NAMESPACE
