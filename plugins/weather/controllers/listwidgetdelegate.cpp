//
// Created by astrea on 9/13/22.
//
#include "listwidgetdelegate.h"
#include "weatherdata.h"
#include "views/listwidget.h"
#include <QPainter>
BEGIN_USER_NAMESPACE
QWidget *ListWidgetDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    auto futureWeather = index.data().value<FutureWeather>();
    auto *w = new ListWidget(&futureWeather, parent);
    w->installEventFilter(w);
    return w;
}

ListWidgetDelegate::ListWidgetDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ListWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(index)
}

QSize ListWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return {LIST_WIDGET_WIDTH + LISTVIEW_ITEM_SPACING, LIST_WIDGET_HEIGHT};
}

void ListWidgetDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    QRect rect = option.rect;
    editor->setGeometry(rect.x(), rect.y(), LIST_WIDGET_WIDTH, LIST_WIDGET_HEIGHT);
}

END_USER_NAMESPACE