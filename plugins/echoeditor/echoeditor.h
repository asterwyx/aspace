// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "plugininterface.h"
#include <QScopedPointer>
#include <QString>
#include <QWidget>
#include <QtGlobal>
#include "common_def.h"
BEGIN_USER_NAMESPACE
class EchoEditorPrivate;
class EchoEditor : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_IID)
    Q_INTERFACES(PluginInterface)

public:
    EchoEditor();
    ~EchoEditor() override;
    QString pluginName() const override;
    QString pluginDisplayName() const override;
    QWidget *pluginWidget(const QString &key) override;

private:
    Q_DECLARE_PRIVATE(EchoEditor)
    QScopedPointer<EchoEditorPrivate> d_ptr;
};
END_USER_NAMESPACE