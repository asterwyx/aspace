#include "qwidgetmock.h"
#include <QWidget>
#include <QDebug>
#include <QResizeEvent>

void updateStub(void *obj)
{
    auto *o = reinterpret_cast<QWidget *>(obj);
    qDebug() << "Function" << __func__ << "is called.";
    o->paintEvent(nullptr);
}

void resizeStub(void *obj, int w, int h) {
    auto *o = reinterpret_cast<QWidget *>(obj);
    qDebug() << "Function" << __func__ << "is called.";
    QResizeEvent event(QSize(w, h), o->size());
    o->resizeEvent(&event);
}
