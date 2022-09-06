#pragma once
#include "common_def.h"
#include <QAbstractItemView>

BEGIN_USER_NAMESPACE

/**
 * @brief A prettified location selection widget
 * 
 */
class LocationSelector : public QAbstractItemView {
public:
    LocationSelector(QWidget *parent = nullptr);
    ~LocationSelector();

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;

    QModelIndex indexAt(const QPoint &point) const override;

protected:
    QModelIndex moveCursor(CursorAction cursorAction,
                                   Qt::KeyboardModifiers modifiers) override;

    int horizontalOffset() const override;

    int verticalOffset() const override;

    bool isIndexHidden(const QModelIndex &index) const override;

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;

    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

};


END_USER_NAMESPACE