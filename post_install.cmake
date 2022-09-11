# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later
# ldconfig and compile schemas
execute_process(
    COMMAND sudo ldconfig
    COMMAND sudo glib-compile-schemas /usr/share/glib-2.0/schemas
)