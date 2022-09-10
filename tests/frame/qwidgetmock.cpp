//
// Created by astrea on 9/8/22.
//
#include "qwidgetmock.h"
#include <QWidget>
#include <QDebug>

//static bool mocked = false;

//static update_t update_func = reinterpret_cast<update_t>(dlsym(RTLD_NEXT, "QWidget::update"));

void update_stub(void *obj)
{
    auto *o = reinterpret_cast<QWidget *>(obj);
    qDebug() << "Function" << __FUNCTION__ << "is called.";
    qDebug() << "Starting paint event!";
    o->paintEvent(nullptr);
//    if (mocked)
//    {
//
//    }
//    else
//    {
////        update_func();
//    }
}

//bool isMocked()
//{
//    return mocked;
//}
//
//void setMocked(bool enable)
//{
//    mocked = enable;
//}