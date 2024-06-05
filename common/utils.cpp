// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "utils.h"
#include "weatherdata.h"
#include <QtDBus>
#include "enumdbus.h"



QDomElement Utils::setXmlAttrValueRecurse(QDomElement elem, const QString &attrName, const QString &attrValue)
{
    if (elem.hasAttribute(attrName)) {
        elem.setAttribute(attrName, attrValue);
    }
    for (int i = 0; i < elem.childNodes().count(); i++) {
        if (!elem.childNodes().at(i).isElement()) {
            continue;
        }
        elem.replaceChild(elem.childNodes().at(i),
                          setXmlAttrValueRecurse(elem.childNodes().at(i).toElement(), attrName, attrValue));
    }
    return elem;
}

void Utils::registerAllMetaTypes()
{
    qRegisterMetaType<TemperatureUnit>("TemperatureUnit");
    qDBusRegisterMetaType<TemperatureUnit>();
    qInfo() << "Meta types for TemperatureUnit registered.";
    Location::registerMetaTypes();
    CurrentWeather::registerMetaTypes();
    FutureWeather::registerMetaTypes();
}
