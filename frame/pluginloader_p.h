// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "pluginloader.h"
#include <QString>
#include <qlist.h>
BEGIN_USER_NAMESPACE
class PluginLoaderPrivate {
public:
    explicit PluginLoaderPrivate(PluginLoader *q);
    ~PluginLoaderPrivate();

protected:
    bool loadPlugins();

private:
    Q_DECLARE_PUBLIC(PluginLoader)
    PluginLoader                    *q_ptr;
    QStringList                     m_pluginDirs;
    QList<PluginInterface *>        m_plugins;
};

END_USER_NAMESPACE
