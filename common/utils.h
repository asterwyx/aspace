// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QDomElement>
class Utils
{
public:
    static QDomElement setXmlAttrValueRecurse(QDomElement elem, const QString &attrName, const QString &attrValue);
    static void registerAllMetaTypes();
};
