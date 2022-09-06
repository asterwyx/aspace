// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "plugininterface.h"
#include <QList>
#include <QScopedPointer>
#include <QtGlobal>
#include "common_def.h"

BEGIN_USER_NAMESPACE
class PluginLoaderPrivate;
class PluginLoader {
public:
    PluginLoader();
    explicit PluginLoader(const QString &pluginDir);
    PluginLoader(const QString &pluginDir, PluginLoaderPrivate &d);
    ~PluginLoader();
    bool                            loadPlugins();
    void                            showAllPlugins(QWidget *parent);
    void                            addPluginDir(QString pluginDir);
    const QList<PluginInterface *>  *getPlugins();

private:
    Q_DECLARE_PRIVATE(PluginLoader)
    QScopedPointer<PluginLoaderPrivate> d_ptr;
};
END_USER_NAMESPACE
