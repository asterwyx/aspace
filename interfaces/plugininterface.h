// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "common_def.h"
#include <QWidget>
#include <QResizeEvent>
#include <QSize>

BEGIN_USER_NAMESPACE
class FrameProxyInterface;
class PluginInterfacePrivate;
class PluginInterface
{
public:
    explicit PluginInterface(FrameProxyInterface *frameProxy = nullptr);
    /**
     * @brief Destroy the Plugin Interface object
     *
     */
    virtual ~PluginInterface();

    /**
     * @brief Initialize a plugin, if frameProxy is nullptr, use m_frameProxy
     * Full initialize of a plugin, after this function, a plugin is fully loaded, and may show on screen.
     * @param frameProxy
     */
    virtual void initialize() = 0;

    /**
     * @brief Can only manipulate data, do not add a parent crossing thread
     *
     */
    virtual void loadData() = 0;

    void setFrameProxy(FrameProxyInterface *frameProxy);

    FrameProxyInterface *frameProxy();

    /**
     * @brief Return the only name of a plugin, this is a must-need name
     *
     * @return const QString
     */
    virtual QString pluginName() const = 0;

    /**
     * @brief Overwrite this function if you want a different display name
     *
     * @return const QString
     */
    virtual QString pluginDisplayName() const { return QObject::tr(""); }

    /**
     * @brief Get the widget of the plugin
     *
     * @param itemKey the only identifier for the plugin
     * @return QWidget* the widget
     */
    virtual QWidget *pluginItemWidget(const QString &itemKey) = 0;

    virtual void adjustSize(QResizeEvent *event, const QMap<QString, QWidget *> &items) = 0;

private:
    Q_DECLARE_PRIVATE(PluginInterface)
    PluginInterfacePrivate *d_ptr;
};

END_USER_NAMESPACE

#define PLUGIN_INTERFACE_IID "org.deepin.aspace.plugin/1.0"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(USER_NAMESPACE::PluginInterface, PLUGIN_INTERFACE_IID)
QT_END_NAMESPACE