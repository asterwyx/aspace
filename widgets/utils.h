#pragma once
#include <QDomElement>
#include "namespace.h"

BEGIN_USER_NAMESPACE
class Utils
{
public:
    static QDomElement setXmlAttrValueRecurse(QDomElement elem, const QString &attrName, const QString &attrValue);
};
END_USER_NAMESPACE
