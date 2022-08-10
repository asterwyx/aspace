// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QWidget>
#include <QDesignerExportWidget>
#include <QColor>
#include <QSize>
#include "namespace.h"

BEGIN_USER_NAMESPACE
class QDESIGNER_WIDGET_EXPORT Battery : public QWidget {
    Q_OBJECT
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(double alarmValue READ getAlarmValue WRITE setAlarmValue)


    Q_PROPERTY(double step READ getStep WRITE setStep)
    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
    Q_PROPERTY(int bgRadius READ getBgRadius WRITE setBgRadius)
    Q_PROPERTY(int headRadius READ getHeadRadius WRITE setHeadRadius)
    
    Q_PROPERTY(QColor borderColorStart READ getBorderColorStart WRITE setBorderColorStart)
    Q_PROPERTY(QColor borderColorEnd READ getBorderColorEnd WRITE setBorderColorEnd)

    Q_PROPERTY(QColor alarmColorStart READ getAlarmColorStart WRITE setAlarmColorStart)
    Q_PROPERTY(QColor alarmColorEnd READ getAlarmColorStart WRITE setAlarmColorEnd)

    Q_PROPERTY(QColor normalColorStart READ getNormalColorStart WRITE setNormalColorStart)
    Q_PROPERTY(QColor normalColorEnd READ getNormalColorEnd WRITE setNormalColorEnd)

public:
    explicit Battery(QWidget *parent = nullptr);
    ~Battery() override;

public:

    double  getMinValue() const { return minValue; }
    double  getMaxValue() const { return maxValue; }
    double  getValue() const { return value; }
    double  getAlarmValue() const { return alarmValue; }

    double  getStep() const { return step; }
    int     getBorderRadius() const { return borderRadius; }
    int     getBgRadius() const { return bgRadius; }
    int     getHeadRadius() const { return headRadius; }

    QColor  getBorderColorStart() const { return borderColorStart; }
    QColor  getBorderColorEnd() const { return borderColorEnd; }

    QColor  getAlarmColorStart() const { return alarmColorStart; }
    QColor  getAlarmColorEnd() const { return alarmColorEnd; }

    QColor  getNormalColorStart() const { return normalColorStart; }
    QColor  getNormalColorEnd() const { return normalColorEnd; }

    QSize   sizeHint()  const override;
    QSize   minimumSizeHint() const override;

public slots:

    void    setRange(double minValue, double maxValue) { this->minValue = minValue; this->maxValue = maxValue; }
    void    setRange(int minValue, int maxValue) { this->minValue = static_cast<double>(minValue); this->maxValue = static_cast<double>(maxValue); }

    void    setMinValue(double minValue) { this->minValue = minValue; }
    void    setMaxValue(double maxValue) { this->maxValue = maxValue; }
    
    void    setValue(double value) { this->value = value; }
    void    setValue(int value) { this->value = static_cast<double>(value); }
    
    void    setAlarmValue(double alarmValue) { this->alarmValue = alarmValue; }
    void    setAlarmValue(int alarmValue) { this->alarmValue = static_cast<double>(alarmValue); }

    void    setStep(double step) { this->step = step; }
    void    setStep(int step) { this->step = static_cast<double>(step); }

    void    setBorderRadius(int borderRadius) { this->borderRadius = borderRadius; }

    void    setBgRadius(int bgRadius) { this->bgRadius = bgRadius; }

    void    setHeadRadius(int headRadius) { this->headRadius = headRadius; }

    void    setBorderColorStart(const QColor &borderColorStart) { this->borderColorStart = borderColorStart; }
    void    setBorderColorEnd(const QColor &borderColorEnd) { this->borderColorEnd = borderColorEnd; }
    

    void    setAlarmColorStart(const QColor &alarmColorStart) { this->alarmColorStart = alarmColorStart; }
    void    setAlarmColorEnd(const QColor &alarmColorEnd) { this->alarmColorEnd = alarmColorEnd; }

    void    setNormalColorStart(const QColor &normalColorStart) { this->normalColorStart = normalColorStart; }
    void    setNormalColorEnd(const QColor &normalColorEnd) { this->normalColorEnd = normalColorEnd; }

protected:
    void    paintEvent(QPaintEvent *event) override;
    void    drawBorder(QPainter *painter);
    void    drawBg(QPainter *painter);
    void    drawHead(QPainter *painter);

private slots:
    void    updateValue();

private:
    double  minValue{};
    double  maxValue{};
    double  value{};
    double  alarmValue{};

    double  step{};
    int     borderRadius{};
    int     bgRadius{};
    int     headRadius{};

    QColor  borderColorStart;
    QColor  borderColorEnd;

    QColor  alarmColorStart;
    QColor  alarmColorEnd;

    QColor  normalColorStart;
    QColor  normalColorEnd;

    bool    m_isForward{};
    double  m_currentValue{};
    QRectF  m_batteryRect;
    QTimer  *m_timer;

};
END_USER_NAMESPACE