//
// Created by astrea on 9/13/22.
//
#include "listwidget.h"

ListWidget::ListWidget(const FutureWeather *weather, QWidget *parent)
    : QGroupBox(parent)
{
    resize(LIST_WIDGET_WIDTH, LIST_WIDGET_HEIGHT);
    m_weatherIcon = new WeatherIcon("", this);
    m_weatherIcon->setIconFromName(weather->iconDay);
    m_weatherIcon->setColor(Qt::yellow);
    m_weatherIcon->setScaleFactor(static_cast<double>(LIST_WIDGET_WIDTH) / m_weatherIcon->width() * 0.8);
    m_weatherIcon->move(LIST_WIDGET_WIDTH * 0.1, LIST_WIDGET_WIDTH * 0.1);
    QFont labelFont("Noto Sans CJK SC");
    labelFont.setWeight(100);
    labelFont.setPointSize(10);
    int unit = LIST_WIDGET_WIDTH / 2;
    m_sunriseTime = new QLabel(QString::fromUtf8("日出时间：%1").arg(weather->sunriseTime.toString()), this);
    m_sunriseTime->resize(LIST_WIDGET_WIDTH, unit);
    m_sunriseTime->move(0, LIST_WIDGET_WIDTH);
    m_sunriseTime->setFont(labelFont);
    m_maxTemperature = new QLabel(QString::fromUtf8("最高温度：%1°").arg(weather->maxTemperature), this);
    m_maxTemperature->resize(LIST_WIDGET_WIDTH, unit);
    m_maxTemperature->move(0, LIST_WIDGET_WIDTH + unit);
    m_maxTemperature->setFont(labelFont);
    m_minTemperature = new QLabel(QString::fromUtf8("最低温度：%1°").arg(weather->minTemperature), this);
    m_minTemperature->resize(LIST_WIDGET_WIDTH, unit);
    m_minTemperature->move(0, LIST_WIDGET_WIDTH + 2 * unit);
    m_minTemperature->setFont(labelFont);
    m_sunsetTime = new QLabel(QString::fromUtf8("日落时间：%1").arg(weather->sunsetTime.toString()), this);
    m_sunsetTime->resize(LIST_WIDGET_WIDTH, unit);
    m_sunsetTime->move(0, LIST_WIDGET_WIDTH + 3 * unit);
    m_sunsetTime->setFont(labelFont);
    m_sunsetTime->setAlignment(Qt::AlignCenter);
    m_sunriseTime->setAlignment(Qt::AlignCenter);
    m_maxTemperature->setAlignment(Qt::AlignCenter);
    m_minTemperature->setAlignment(Qt::AlignCenter);
    setFixedHeight(LIST_WIDGET_HEIGHT);
}

ListWidget::~ListWidget() {}
