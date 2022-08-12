// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QObject>
#include <QWidget>

#include "global.h"

BEGIN_USER_NAMESPACE
class WeatherIconPrivate;
class  WeatherIcon : public QWidget
{
    Q_OBJECT

public:
    enum IconType {
        PNG,
        SVG
    };

public:
    explicit WeatherIcon(const QString& iconPath, QWidget *parent = nullptr, double scaleFactor = 1.0, IconType type = SVG);
    ~WeatherIcon() override;
    void setSvgColor(QColor color = Qt::yellow);
    void setIcon(const QString& iconPath, IconType type = SVG);

protected:
    void paintEvent(QPaintEvent *event) override;
    void loadSvgData();
    
    

private:
    Q_DECLARE_PRIVATE(WeatherIcon)
    QScopedPointer<WeatherIconPrivate> d_ptr;
};
END_USER_NAMESPACE
