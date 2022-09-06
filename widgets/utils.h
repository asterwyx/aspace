// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QDomElement>
#include "common_def.h"

BEGIN_USER_NAMESPACE
class Utils
{
public:
    static QDomElement setXmlAttrValueRecurse(QDomElement elem, const QString &attrName, const QString &attrValue);
};
END_USER_NAMESPACE
