#pragma once
#include "common_def.h"
#include <QAbstractButton>
#include <QScopedPointer>


namespace utils {
QColor revertColor(const QColor &color);
QColor brightenColor(const QColor &color);
QColor darkenColor(const QColor &color);
};  // namespace utils
class HoverButtonPrivate;
class Q_DECL_IMPORT HoverButton : public QAbstractButton
{
public:
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)

    explicit HoverButton(QWidget *parent = nullptr);
    ~HoverButton() override = default;
    QColor background();
    QWidget *backgroundWidget();
    int borderRadius();
    void setBackground(const QColor &background);
    void setBackgroundWidget(QWidget *widget);
    void setBorderRadius(int radius);
    void getBackgroundFromWidget(QWidget *parent);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void setIconSize(const QSize &size);
    void setIconSize(const int w, const int h);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    Q_DECLARE_PRIVATE(HoverButton)
    QScopedPointer<HoverButtonPrivate> d_ptr;
};
