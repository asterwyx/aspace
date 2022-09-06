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

    void addItem(PluginInterface *pluginToAdd, const QString &itemKey) override;
    void removeItem(const QString &itemKey) override;
    void updateItem(const QString &itemKey) override;
    QSize getFrameSize() override;
    void initializeAllPlugins() override;
    void addPlugin(PluginInterface *plugin) override;

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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QMap<QString, QWidget *>                            m_itemMap;
    QList<PluginInterface *>                            m_plugins;
    QGSettings                                          *m_windowSettings;
    bool                                                m_saveLastWindowSize;
};

END_USER_NAMESPACE
