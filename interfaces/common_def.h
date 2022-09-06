// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#if not defined(DBUS_SERVICE_NAME)
#define DBUS_SERVICE_NAME               "org.deepin.aspace"
#endif
#define DBUS_WEATHER_INTERFACE_NAME     DBUS_SERVICE_NAME".Weather"
#define DBUS_ASPACE_PATH                "/org/deepin/aspace"

#define USER_NAMESPACE                  aspace
#define USE_USER_NAMESPACE              using namespace USER_NAMESPACE;
#define BEGIN_USER_NAMESPACE            namespace USER_NAMESPACE {
#define END_USER_NAMESPACE              }

#if not defined(SCHEMA_ID)
#define SCHEMA_ID                       "org.deepin.aspace"
#endif

#if not defined(SCHEMA_PATH)
#define SCHEMA_PATH                     "/org/deepin/aspace/"
#endif

#if not defined(PLUGIN_DIR)
#define PLUGIN_DIR                      "/usr/lib/aspace/plugins"
#endif