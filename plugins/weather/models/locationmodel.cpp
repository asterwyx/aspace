#include "locationmodel.h"

BEGIN_USER_NAMESPACE

LocationModel::LocationModel(QObject *parent)
    : QObject(parent)
    , m_location{}
{
}

void LocationModel::setLocation(const Location &location)
{
    m_location = location;
}

Location LocationModel::getLocation()
{
    return m_location;
}

QString LocationModel::getLocationId()
{
    return m_location.id;
}

END_USER_NAMESPACE
