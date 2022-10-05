// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QDBusArgument>
#include <type_traits>

template <typename T, typename TEnum>
class QDBusEnumMarshal;

template <typename T>
class QDBusEnumMarshal<T, std::true_type>
{
public:
    static QDBusArgument &marshal(QDBusArgument &argument, const T &source)
    {
        argument.beginStructure();
        argument << static_cast<int>(source);
        argument.endStructure();
        return argument;
    }

    static const QDBusArgument &unmarshal(const QDBusArgument &argument, T &source)
    {
        int a;
        argument.beginStructure();
        argument >> a;
        argument.endStructure();

        source = static_cast<T>(a);

        return argument;
    }
};

template <typename T>
QDBusArgument &operator<<(QDBusArgument &argument, const T &source)
{
    return QDBusEnumMarshal<T, typename std::is_enum<T>::type>::marshal(argument, source);
}

template <typename T>
const QDBusArgument &operator>>(const QDBusArgument &argument, T &source)
{
    return QDBusEnumMarshal<T, typename std::is_enum<T>::type>::unmarshal(argument, source);
}
