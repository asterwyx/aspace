#include "futureweathermodel.h"
#include <utility>


FutureWeatherModel::FutureWeatherModel(ListView *list, QObject *parent)
    : QAbstractListModel(parent)
    , m_list(list)
{
}

int FutureWeatherModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_futureWeather.size();
}

int FutureWeatherModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

void FutureWeatherModel::clear()
{
    beginResetModel();
    m_futureWeather.clear();
    endResetModel();
}

void FutureWeatherModel::onFutureWeatherUpdated(const QList<FutureWeather> &futureWeather)
{
    this->clear();
    foreach (const FutureWeather &weather, futureWeather) {
        beginInsertRows(QModelIndex(), 0, 0);
        m_futureWeather.append(weather);
        endInsertRows();
    }
    qDebug() << "Future weather got, size:" << futureWeather.size();
    emit this->dataChanged();
}

QVariant FutureWeatherModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    if (index.isValid() && index.row() < m_futureWeather.size()) {
        FutureWeather futureWeather = m_futureWeather.at(index.row());
        return QVariant::fromValue(futureWeather);
    }
    return QVariant();
}

Qt::ItemFlags FutureWeatherModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (m_list)
            m_list->openPersistentEditor(index);
        return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractListModel::flags(index);
}

void FutureWeatherModel::setList(ListView *list)
{
    m_list = list;
}

ListView *FutureWeatherModel::list()
{
    return m_list;
}
