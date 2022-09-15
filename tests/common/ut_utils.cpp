#include <gtest/gtest.h>
#include "utils.h"
#include <QFile>
#include <QSvgRenderer>
#include <QColor>

USE_USER_NAMESPACE

//TEST(UtilsTest, setXmlAttrValueRecurse)
//{
//    QColor color(Qt::yellow);
//    QFile icon(":/icons/100.svg");
//    icon.open(QIODevice::ReadOnly);
//    QByteArray data = icon.readAll();
//    QDomDocument doc;
//    doc.setContent(data);
//    QString colorString = QString::asprintf("rgb(%d,%d,%d)", color.red(), color.green(), color.blue());
//    auto elem = doc.documentElement();
//    elem = Utils::setXmlAttrValueRecurse(doc.documentElement(), "fill", colorString);
//    doc.replaceChild(doc.documentElement(), elem);
//    data = doc.toByteArray();
//    QSvgRenderer renderer;
//    renderer.load(data);
//}