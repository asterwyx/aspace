// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QObject>
#include <QWidget>

#include "common_def.h"

BEGIN_USER_NAMESPACE
class WeatherIconPrivate;
/**
 * @brief SVG Weather Icon
 */
class WeatherIcon : public QWidget
{
    Q_OBJECT
public:
    explicit WeatherIcon(const QString &iconPath = "", QWidget *parent = nullptr, double scaleFactor = 1.0);
    ~WeatherIcon();
    void setColor(QColor color = Qt::yellow);
    void setIconFromPath(const QString &iconPath);
    void setIconFromName(const QString &iconName);
    void setScaleFactor(double scaleFactor);

    double scaleFactor() const;
    QColor color() const;
    bool isLoaded() const;
    QString iconPath() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void loadData();

private:
    Q_DECLARE_PRIVATE(WeatherIcon)
    QScopedPointer<WeatherIconPrivate> d_ptr;
};
END_USER_NAMESPACE
