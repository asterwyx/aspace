#pragma once
#include "frameproxyinterface.h"
#include "plugininterface.h"

#include <QMainWindow>
#include <QMap>
#include <QPair>
#include <QGSettings>

BEGIN_USER_NAMESPACE


class MainWindow : public QMainWindow, public FrameProxyInterface
{
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void itemAdded(PluginInterface *pluginToAdd, const QString &itemKey) override;
    void itemRemoved(const QString &itemKey) override;
    void itemUpdated(const QString &itemKey) override;
    QSize getSize() override;

    // Window size
    void loadDefaultSize();
    bool isSaveLastWindowSize();
    void setSaveLastWindowSize(bool enable);
    /**
     * Set GSettings window width and height, notice that this function will not resize the window, just write the config.
     * For a separate storage, width is set first and then height, it is possible that width is set but height is not. Be careful.
     * @param size size to set
     */
    void setSize(const QSize &size);


private:
    QMap<QString, QPair<PluginInterface *, QWidget *>>  m_itemMap;
    QList<PluginInterface *>                            m_plugins;
    QGSettings                                          *m_windowSettings;
    bool                                                m_saveLastWindowSize;
};

END_USER_NAMESPACE
