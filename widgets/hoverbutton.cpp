#include "hoverbutton.h"
#include "hoverbutton_p.h"
#include <QPainter>
#include <QIcon>
#include <QStyle>
#include <QPointer>
#include <QStyleOption>
#include <QWidget>
#include <QPaintEvent>
#include <private/qabstractbutton_p.h>

BEGIN_USER_NAMESPACE
namespace utils {
QColor revertColor(const QColor &color)
{
    QColor result;
    result.setRed(255 - color.red());
    result.setGreen(255 - color.green());
    result.setBlue(255 - color.blue());
    return result;
}
/**
 * This function will brighten the color a little
 * @param color
 * @return
 */
QColor brightenColor(const QColor &color)
{
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    int minFactor = qMin(qMin(red, green), blue);
    int delta = minFactor / 5;
    red += delta;
    green += delta;
    blue += delta;
    red = qMin(255, red);
    green = qMin(255, green);
    blue = qMin(255, blue);
    return {red, green, blue};
}


/**
 * This function will darken the color a little
 * @param color
 * @return
 */
QColor darkenColor(const QColor &color)
{
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    int maxFactor = qMax(qMax(red, green), blue);
    int delta = maxFactor / 5;
    red -= delta;
    green -= delta;
    blue -= delta;
    red = qMax(0, red);
    green = qMax(0, green);
    blue = qMax(255, blue);
    return {red, green, blue};
}

};
HoverButton::HoverButton(QWidget *parent)
: QAbstractButton(parent), d_ptr(new HoverButtonPrivate(this))
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

void HoverButton::paintEvent(QPaintEvent *e) {
    Q_D(HoverButton);
    Q_UNUSED(e)
    getBackgroundFromWidget(parentWidget());
    QIcon savedIcon = this->icon();
    QSize requestSize = iconSize();
    requestSize = savedIcon.actualSize(requestSize);
    this->resize(requestSize / 5 + requestSize);
    QPainter painter(this);
//    // Set background
//    QPalette pal(this->palette());
//    pal.setBrush(QPalette::Window, d->m_background);
//    QPointer<HoverButton> thisGuard(this);
//    this->setAutoFillBackground(true);
//    this->setPalette(pal);
    // draw background
    QColor backgroundColor;
    if (d->m_hovered)
    {
        backgroundColor = utils::brightenColor(background());
    }
    else
    {
        backgroundColor = background();
    }
    painter.save();
    painter.setBrush(QBrush(backgroundColor));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(0, 0, size().width(), size().height(), borderRadius(), borderRadius());
    painter.restore();
    savedIcon.paint(&painter, requestSize.width() / 10, requestSize.height() / 10, requestSize.width(), requestSize.height());
}

QColor HoverButton::background() {
    Q_D(HoverButton);
    return d->m_background;
}

void HoverButton::setBackground(const QColor &background) {
    Q_D(HoverButton);
    d->setBackground(background);
}

void HoverButton::getBackgroundFromWidget(QWidget *parent) {
    Q_D(HoverButton);
    const QPalette& pal = parent->palette();
    const QBrush& brush = pal.window();
    d->m_background = brush.color();
}

int HoverButton::borderRadius() {
    Q_D(HoverButton);
    return d->m_borderRadius;
}

void HoverButton::setBorderRadius(int radius) {
    Q_D(HoverButton);
    d->m_borderRadius = radius;
}

void HoverButton::enterEvent(QEvent *event) {
    Q_D(HoverButton);
    d->m_hovered = true;
    QWidget::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event) {
    Q_D(HoverButton);
    d->m_hovered = false;
    QWidget::leaveEvent(event);
}

void HoverButton::setIconSize(const QSize &size) {
    resize(size / 5 + size);
    QAbstractButton::setIconSize(size);
}

QSize HoverButton::sizeHint() const {
    auto *bp = dynamic_cast<QAbstractButtonPrivate *>(QAbstractButton::d_ptr.data());
    if (bp->sizeHint.isValid())
    {
        return bp->sizeHint;
    }
    bp->sizeHint = this->size();
    return bp->sizeHint;
}


HoverButtonPrivate::HoverButtonPrivate(HoverButton *q)
: q_ptr(q), m_background(), m_borderRadius(0), m_hovered(false)
{}

void HoverButtonPrivate::setBackground(const QColor &background) {
    m_background = background;
}
END_USER_NAMESPACE


