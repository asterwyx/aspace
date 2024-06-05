// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#if not defined(DBUS_SERVICE_NAME)
#    define DBUS_SERVICE_NAME "org.deepin.aspace"
#endif
#define DBUS_WEATHER_INTERFACE_NAME DBUS_SERVICE_NAME ".Weather"
#define DBUS_ASPACE_PATH "/org/deepin/aspace"
#define DCONFIG_FILE "org.deepin.aspace"

#if not defined(SCHEMA_ID)
#    define SCHEMA_ID "org.deepin.aspace"
#endif

#if not defined(SCHEMA_PATH)
#    define SCHEMA_PATH "/org/deepin/aspace/"
#endif

#if not defined(PLUGIN_DIR)
#    define PLUGIN_DIR "/usr/lib/aspace/plugins"
#endif

static constexpr int LIST_WIDGET_WIDTH = 160;
static constexpr int LIST_WIDGET_HEIGHT = 480;
static constexpr int LISTVIEW_ITEM_SPACING = 20;
