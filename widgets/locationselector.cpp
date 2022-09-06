#include "locationselector.h"
BEGIN_USER_NAMESPACE

LocationSelector::LocationSelector(QWidget *parent) : QAbstractItemView(parent)
{
}

LocationSelector::~LocationSelector() {}

QRect LocationSelector::visualRect(const QModelIndex &index) const
{
    return rect();
}

void LocationSelector::scrollTo(const QModelIndex &index, ScrollHint hint)
{

}

QModelIndex LocationSelector::indexAt(const QPoint &point) const
{
    return QModelIndex();
}

QModelIndex LocationSelector::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}


int LocationSelector::horizontalOffset() const
{
    return 0;
}

int LocationSelector::verticalOffset() const
{
    return 0;
}

bool LocationSelector::isIndexHidden(const QModelIndex &index) const
{
    return false;
}

void LocationSelector::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command)
{
}

QRegion LocationSelector::visualRegionForSelection(const QItemSelection &selection) const
{
    return QRegion();
}


END_USER_NAMESPACE
