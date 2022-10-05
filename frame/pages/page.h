#pragma once
#include "common_def.h"
#include <QWidget>
#include "mainwindow.h"
#include <QPointer>
#include <DConfig>
#include <QGSettings>

DCORE_USE_NAMESPACE
BEGIN_USER_NAMESPACE

class Page : public QWidget
{
    Q_OBJECT
public:
    Page(MainWindow *parent = nullptr);
    QPointer<DConfig> dConfig();
    QPointer<QGSettings> gSettings();

protected:
    MainWindow *m_window;
};

END_USER_NAMESPACE
