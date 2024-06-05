// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "plugininterface.h"
#include "frameproxyinterface.h"
#include <QList>
#include <QScopedPointer>
#include <QtGlobal>
#include "common_def.h"


class PluginLoaderPrivate;
class PluginLoader
{
public:
    PluginLoader();
    explicit PluginLoader(const QString &pluginDir);
    ~PluginLoader();
    bool loadPlugins(FrameProxyInterface *proxy);
    void addPluginDir(QString pluginDir);
    const QList<PluginInterface *> *getPlugins();

private:
    Q_DECLARE_PRIVATE(PluginLoader)
    QScopedPointer<PluginLoaderPrivate> d_ptr;
};
