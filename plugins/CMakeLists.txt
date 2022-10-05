# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later
set(CMAKE_INSTALL_PLUGINDIR "lib/aspace/plugins")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/plugins/all")
# add_subdirectory("echoeditor")
add_subdirectory("weather")
# add_subdirectory("power")