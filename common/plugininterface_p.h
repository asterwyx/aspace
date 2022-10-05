#include "plugininterface.h"

BEGIN_USER_NAMESPACE

class PluginInterfacePrivate
{
public:
    PluginInterfacePrivate(PluginInterface *q)
        : q_ptr(q)
        , m_frameProxy(nullptr)
    {
    }
    ~PluginInterfacePrivate() = default;

    void setFrameProxy(FrameProxyInterface *frameProxy);
    FrameProxyInterface *frameProxy();

private:
    Q_DECLARE_PUBLIC(PluginInterface)
    PluginInterface *q_ptr;
    FrameProxyInterface *m_frameProxy;
};
END_USER_NAMESPACE