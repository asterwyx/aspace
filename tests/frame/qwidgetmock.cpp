#include "qwidgetmock.h"
#include <QWidget>
#include <QDebug>

void update_stub(void *obj)
{
    auto *o = reinterpret_cast<QWidget *>(obj);
    qDebug() << "Function" << __FUNCTION__ << "is called.";
    qDebug() << "Starting paint event!";
    o->paintEvent(nullptr);
}