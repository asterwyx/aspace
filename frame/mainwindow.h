#pragma once
#include "frameproxyinterface.h"
#include "plugininterface.h"

#include <DMainWindow>
#include <QMap>
#include <QPair>
#include <QGSettings>
#include <DConfig>
#include <ostream>
#include <QHBoxLayout>
#include "hoverbutton.h"
#include "loadingpage.h"

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE
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
    QList<PluginInterface *> plugins() override;

    void loadData();
    void showContents();
    void showSplash();
    QPointer<QGSettings> getWindowSettings();
    QPointer<DConfig> getDConfig();
public slots:
    void refresh();

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QMap<QString, QWidget *> m_itemMap;
    QList<PluginInterface *> m_plugins;
    QGSettings *m_windowSettings;
    DConfig *m_dConfig;
    HoverButton *m_refreshButton;
    QWidget *m_contentFrame;
    QVBoxLayout *m_contentLayout;
    LoadingPage *m_loadingPage;
};

END_USER_NAMESPACE
