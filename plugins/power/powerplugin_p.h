// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "powerplugin.h"
#include "battery.h"

BEGIN_USER_NAMESPACE
class PowerPluginPrivate {
public:
    PowerPluginPrivate(PowerPlugin *q);
    ~PowerPluginPrivate();
private:
    Q_DECLARE_PUBLIC(PowerPlugin)
    PowerPlugin *q_ptr;
};
END_USER_NAMESPACE