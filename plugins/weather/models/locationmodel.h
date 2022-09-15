#pragma once
#include "common_def.h"
#include <QObject>
#include "weatherdata.h"


BEGIN_USER_NAMESPACE

class LocationModel : public QObject {
    Q_OBJECT
public:
    explicit LocationModel(QObject *parent = nullptr);

    void setLocation(const Location &location);
    Location getLocation();

    QString getLocationId();

signals:
    void locationChanged(const Location &location);


private:
    Location    m_location;
};

END_USER_NAMESPACE
