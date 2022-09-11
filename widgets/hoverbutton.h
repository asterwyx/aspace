#pragma once
#include "common_def.h"
#include <QAbstractButton>
#include <QScopedPointer>

BEGIN_USER_NAMESPACE
namespace utils {
QColor revertColor(const QColor &color);
QColor brightenColor(const QColor &color);
QColor darkenColor(const QColor &color);
};
class HoverButtonPrivate;
class Q_DECL_IMPORT HoverButton : public QAbstractButton {
public:

    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)

    explicit HoverButton(QWidget *parent = nullptr);
    ~HoverButton() override = default;
    QColor background();
    void setBackground(const QColor &background);
    int borderRadius();
    void setBorderRadius(int radius);

    void getBackgroundFromWidget(QWidget *parent);

    QSize sizeHint() const override;

public slots:
    void setIconSize(const QSize &size);

protected:
    void paintEvent(QPaintEvent *e) override;
    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;

private:
    Q_DECLARE_PRIVATE(HoverButton)
    QScopedPointer<HoverButtonPrivate> d_ptr;
};

END_USER_NAMESPACE


