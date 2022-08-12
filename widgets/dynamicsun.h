// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QWidget>
#include <QDesignerExportWidget>
#include "global.h"

BEGIN_USER_NAMESPACE
class QDESIGNER_WIDGET_EXPORT DynamicSun : public QWidget {
    Q_OBJECT

    Q_PROPERTY(int m_timerInterval READ getTimerInterval WRITE setTimerInterval)
    Q_PROPERTY(int m_animationTime READ getAnimationTime WRITE setAnimationTime)
    Q_PROPERTY(double m_sunRadius READ getSunRadius WRITE setSunRadius)
    Q_PROPERTY(QSizeF m_sunLightSize READ getSunLightSize WRITE setSunLightSize)
    Q_PROPERTY(QColor m_sunColor READ getSunColor WRITE setSunColor)
    Q_PROPERTY(QColor m_sunLightColor READ getSunLightColor WRITE setSunLightColor)

public:
    int     getTimerInterval() const { return m_timerInterval; }
    int     getAnimationTime() const { return m_animationTime; }
    double  getSunRadius() const { return m_sunRadius; }
    QSizeF  getSunLightSize() const { return m_sunLightSize; }
    QColor  getSunColor() const { return m_sunColor; }
    QColor  getSunLightColor() const { return m_sunLightColor; }
    void    setTimerInterval(int timerInterval) { m_timerInterval = timerInterval; }
    void    setAnimationTime(int animationTime) { m_animationTime = animationTime; }
    void    setSunRadius(double sunRadius) { m_sunRadius = sunRadius; }
    void    setSunLightSize(const QSizeF& sunLightSize) { m_sunLightSize = sunLightSize; }
    void    setSunColor(const QColor& sunColor) { m_sunColor = sunColor; }
    void    setSunLightColor(const QColor& sunLightColor) { m_sunLightColor = sunLightColor; }
public:
    explicit DynamicSun(QWidget *parent = nullptr);
    ~DynamicSun() override;
    void resize(int width, int height);

protected:
    void paintEvent(QPaintEvent *event) override;
    void initSize();
    void drawSun(QPainter *painter) const;
    void drawSunLight(QPainter *painter);

private slots:
    void updateView();


private:
    QTimer      *m_timer;
    int         m_timerInterval;
    int         m_animationTime;
    int         m_currentBaseAngle;
    int         m_rotateAngleStep;
    int         m_currentTimerCount;
    double      m_sunRadius;
    QSizeF      m_sunLightSize;
    QColor      m_sunColor;
    QColor      m_sunLightColor;

};

END_USER_NAMESPACE