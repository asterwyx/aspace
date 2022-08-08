#include "utils.h"

BEGIN_USER_NAMESPACE

QDomElement Utils::setXmlAttrValueRecurse(QDomElement elem, const QString &attrName, const QString &attrValue)
{
    if (elem.hasAttribute(attrName))
    {
        elem.setAttribute(attrName, attrValue);
    }
    for (int i = 0; i < elem.childNodes().count(); i++)
    {
        if (!elem.childNodes().at(i).isElement()) {
            continue;
        }
        elem.replaceChild(elem.childNodes().at(i), setXmlAttrValueRecurse(elem.childNodes().at(i).toElement(), attrName, attrValue));
    }
    return elem;
}

END_USER_NAMESPACE
