#pragma once
#include <QObject>
#include <QWidget>
#include "namespace.h"

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
    explicit WeatherIcon(const QString& iconPath, double scaleFactor = 1.0, IconType type = SVG, QWidget *parent = nullptr);
    ~WeatherIcon() override;
    void setSvgColor(QColor color = Qt::yellow);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DECLARE_PRIVATE(WeatherIcon)
    QScopedPointer<WeatherIconPrivate> d_ptr;
};
END_USER_NAMESPACE
