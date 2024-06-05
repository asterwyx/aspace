#pragma once
#include "common_def.h"
#include <QAbstractListModel>
#include "views/listview.h"
#include <QPointer>
#include "weatherdata.h"


class FutureWeatherModel : public QAbstractListModel
{
    Q_OBJECT
public slots:
    void clear();

public:
    explicit FutureWeatherModel(ListView *list, QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void setList(ListView *list);
    ListView *list();

signals:
    void dataChanged();

public slots:
    void onFutureWeatherUpdated(const QList<FutureWeather> &futureWeather);

private:
    QList<FutureWeather> m_futureWeather;
    ListView *m_list;
};
