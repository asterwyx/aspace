#pragma once
#include "common_def.h"
#include <QWidget>
#include <QPointer>
#include <DConfig>
#include <QGSettings>

DCORE_USE_NAMESPACE

class MainWindow;
class Page : public QWidget
{
    Q_OBJECT
public:
    Page(MainWindow *parent = nullptr);
    QPointer<DConfig> dConfig();
    QPointer<QGSettings> gSettings();
    QPointer<DConfig> writeDConfig();

protected:
    MainWindow *m_window;
};
