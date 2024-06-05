#include "plugininterface.h"
#include "plugininterface_p.h"



PluginInterface::PluginInterface(FrameProxyInterface *frameProxy)
    : d_ptr(new PluginInterfacePrivate(this))
{
    this->setFrameProxy(frameProxy);
}

void PluginInterface::setFrameProxy(FrameProxyInterface *frameProxy)
{
    Q_D(PluginInterface);
    d->setFrameProxy(frameProxy);
}

FrameProxyInterface *PluginInterface::frameProxy()
{
    Q_D(PluginInterface);
    return d->frameProxy();
}

void PluginInterfacePrivate::setFrameProxy(FrameProxyInterface *frameProxy)
{
    m_frameProxy = frameProxy;
}

PluginInterface::~PluginInterface()
{
    delete d_ptr;
}

FrameProxyInterface *PluginInterfacePrivate::frameProxy()
{
    return m_frameProxy;
}
