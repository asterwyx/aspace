#pragma once

#include "common_def.h"
#include <QListView>



class ListView : public QListView
{
    Q_OBJECT
public:
    explicit ListView(QWidget *parent = nullptr);

    virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
};
