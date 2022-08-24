// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
WeatherIcon::WeatherIcon(const QString& iconPath, QWidget *parent, double scaleFactor)
    : QWidget(parent), d_ptr(new WeatherIconPrivate(this))
{
    Q_D(WeatherIcon);
    d->m_scaleFactor = scaleFactor;
    d->m_iconPath = iconPath;
    loadData();
}

void WeatherIcon::setColor(QColor color)
{
    Q_D(WeatherIcon);
    d->m_iconColor = color;
    if (!d->m_loaded)
        return;
    QDomDocument doc;
    doc.setContent(d->m_svgData);
    int red, green, blue;
    color.getRgb(&red, &green, &blue);
    QString colorString = QString::asprintf("rgb(%d,%d,%d)", red, green, blue);
    auto elem = doc.documentElement();
    elem = Utils::setXmlAttrValueRecurse(doc.documentElement(), "fill", colorString);
    doc.replaceChild(doc.documentElement(), elem);
    d->m_svgData = doc.toByteArray();
}

void WeatherIcon::loadData()
{
    Q_D(WeatherIcon);
    d->m_loaded = !d->m_iconPath.isEmpty();
    if (d->m_loaded)
    {
        QFile iconFile(d->m_iconPath);
        iconFile.open(QIODevice::ReadOnly);
        d->m_svgData = iconFile.readAll();
        iconFile.close();
        setColor(d->m_iconColor); // Sync color setting
    }
}

void WeatherIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(WeatherIcon);
    if (d->m_loaded)
    {
        QSvgRenderer renderer;
        renderer.load(d->m_svgData);
        auto size = renderer.defaultSize();
        QPixmap pixmap(size * d->m_scaleFactor);
        resize(pixmap.size());
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing);
        renderer.render(&painter);
        painter.end();
        painter.begin(this);
        painter.drawPixmap(0, 0, pixmap);
    }
}

void WeatherIcon::setIconFromPath(const QString& iconPath)
{
    Q_D(WeatherIcon);
    d->m_iconPath = iconPath;
    loadData();
    this->update();
}

void WeatherIcon::setIconFromName(const QString &iconName)
{
    if (iconName.isEmpty())
        return;
    setIconFromPath(":icons/" + iconName + ".svg");
}

WeatherIcon::~WeatherIcon() = default;

WeatherIconPrivate::WeatherIconPrivate(WeatherIcon *q) : q_ptr(q) {}
WeatherIconPrivate::~WeatherIconPrivate() = default;
END_USER_NAMESPACE
