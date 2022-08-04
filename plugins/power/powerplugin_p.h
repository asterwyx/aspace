#pragma once
#include "powerplugin.h"
#include "battery.h"

namespace dspace {
class PowerPluginPrivate {
public:
    PowerPluginPrivate(PowerPlugin *q);
    ~PowerPluginPrivate();
private:
    Q_DECLARE_PUBLIC(PowerPlugin)
    PowerPlugin *q_ptr;
};
}