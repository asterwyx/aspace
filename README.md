<!--
SPDX-FileCopyrightText: 2022 Astrea Wang

SPDX-License-Identifier: GPL-3.0-or-later
-->

# Aspace

Aspace is a module for dde providing weather service and other plugins.

## Cautions

We provide a way to build and install from source. It's free to specify you own install prefix, but please make sure that you install prefix point to a valid path included in ld.conf or ld.conf.so.d/*. Otherwise the dynamic linker will not find the dynamic library in runtime.

You may say that we can add your CMAKE_INSTALL_LIBDIR to ld.conf lists. Yes, it works. But it's a little bit dirty, and it needs root privilege. So, just make sure you specify the appropriate install prefix like /usr or /usr/local which is in most distributions' linker list. We recommend you using debian package tool and install from deb. This is way much cleaner and easier to control.
