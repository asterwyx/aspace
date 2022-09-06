#pragma once
#include "common_def.h"
#include <QAbstractListModel>

BEGIN_USER_NAMESPACE

class LocationModel : public QAbstractListModel {
public:
    explicit LocationModel(QObject *parent = nullptr);
    ~LocationModel();
    
};

END_USER_NAMESPACE
