//
// Created by astrea on 9/8/22.
//
#pragma once
#include <QWidget>
#include <dlfcn.h>

typedef void (*update_t) ();


bool isMocked();
void setMocked(bool enable);
