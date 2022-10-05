//
// Created by astrea on 9/13/22.
//
#include "listview.h"
BEGIN_USER_NAMESPACE
ListView::ListView(QWidget *parent)
    : QListView(parent)
{
    setAutoFillBackground(false);
    viewport()->setAutoFillBackground(false);

    setSelectionMode(QListView::NoSelection);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollMode(QListView::ScrollPerPixel);

    setMouseTracking(true);
    viewport()->setMouseTracking(true);
    setFlow(QListView::LeftToRight);
    // this->setViewMode(QListView::IconMode);
}

void ListView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    Q_UNUSED(index);
    Q_UNUSED(hint);
}

END_USER_NAMESPACE