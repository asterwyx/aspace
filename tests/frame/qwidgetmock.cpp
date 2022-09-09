//
// Created by astrea on 9/8/22.
//
#include "qwidgetmock.h"
#include <QDebug>

static bool mocked = false;

static update_t update_func = reinterpret_cast<update_t>(dlsym(RTLD_NEXT, "QWidget::update"));

void QWidget::update()
{
    qDebug() << "Function" << __FUNCTION__ << "is called.";
    if (mocked)
    {
        qDebug() << "Starting paint event!";
        this->paintEvent(nullptr);
    }
    else
    {
        update_func();
    }
}

bool isMocked()
{
    return mocked;
}

void setMocked(bool enable)
{
    mocked = enable;
}