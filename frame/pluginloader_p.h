// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "pluginloader.h"
#include <QString>
#include <QList>

class PluginLoaderPrivate
{
public:
    explicit PluginLoaderPrivate(PluginLoader *q);
    ~PluginLoaderPrivate();

protected:
    bool loadPlugins(FrameProxyInterface *proxy);

private:
    Q_DECLARE_PUBLIC(PluginLoader)
    PluginLoader *q_ptr;
    QStringList m_pluginDirs;
    QList<PluginInterface *> m_plugins;
};
