#pragma once

#include "common_def.h"
#include <QListView>

BEGIN_USER_NAMESPACE

class ListView : public QListView {
    Q_OBJECT
public:
    explicit ListView(QWidget *parent = nullptr);

    virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;

};

END_USER_NAMESPACE
