#pragma once
#include "frameproxyinterface.h"
#include "plugininterface.h"

#include <DMainWindow>
#include <QMap>
#include <QPair>
#include <QGSettings>
#include <ostream>
#include <QHBoxLayout>
#include "hoverbutton.h"
#include "loadingpage.h"

DWIDGET_USE_NAMESPACE
BEGIN_USER_NAMESPACE
class MainWindow : public DMainWindow, public FrameProxyInterface
{
public:

    Q_PROPERTY(bool saveLastWindowSize READ saveLastWindowSize WRITE setSaveLastWindowSize)

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void addItem(PluginInterface *pluginToAdd, const QString &itemKey) override;
    void removeItem(const QString &itemKey) override;
    void updateItem(const QString &itemKey) override;
    QSize getFrameSize() override;
    
    void initializeAllPlugins() override;
    void pluginAdded(PluginInterface *plugin) override;
    void loadData();

    QList<PluginInterface *> plugins() override;

    // Window size
    // void loadDefaultSize();
    // [[nodiscard]] bool saveLastWindowSize() const;
    // void setSaveLastWindowSize(bool enable);
    /**
     * Set GSettings window width and height, notice that this function will not resize the window, just write the config.
     * For a separate storage, width is set first and then height, it is possible that width is set but height is not. Be careful.
     * @param size size to set
     */
    // void setSize(const QSize &size);
    // void setSize(int width, int height);

    void showContents();
    void showSplash();
    QGSettings *getWindowSettings();
public slots:
    void refresh();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QMap<QString, QWidget *>    m_itemMap;
    QList<PluginInterface *>    m_plugins;
    QGSettings                  *m_windowSettings;
    HoverButton                 *m_refreshButton;
    QWidget                     *m_infoArea;
    QWidget                     *m_contentFrame;
    QHBoxLayout                 *m_infoLayout;
    QVBoxLayout                 *m_contentLayout;
    LoadingPage                 *m_loadingPage;
};

END_USER_NAMESPACE
