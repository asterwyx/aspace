// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#if not defined(DBUS_SERVICE_NAME)
#define DBUS_SERVICE_NAME               "org.deepin.aspace"
#endif
#define DBUS_WEATHER_INTERFACE_NAME     DBUS_SERVICE_NAME".Weather"

#if not defined(DBUS_PATH_PREFIX) 
#define DBUS_PATH_PREFIX                "/org/deepin/aspace/"
#endif
#define DBUS_WEATHER_PATH               DBUS_PATH_PREFIX"weather"

#define USER_NAMESPACE aspace
#define USE_USER_NAMESPACE              using namespace USER_NAMESPACE;
#define BEGIN_USER_NAMESPACE            namespace USER_NAMESPACE {
#define END_USER_NAMESPACE              }
