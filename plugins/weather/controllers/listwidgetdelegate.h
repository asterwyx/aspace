#pragma once
#include "common_def.h"
#include <QStyledItemDelegate>

BEGIN_USER_NAMESPACE

class ListWidgetDelegate : public QStyledItemDelegate
{
public:
    explicit ListWidgetDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

END_USER_NAMESPACE
