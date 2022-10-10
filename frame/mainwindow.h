#pragma once
#include "plugininterface.h"

#include <DMainWindow>
#include <QMap>
#include <QPair>
#include <QGSettings>
#include <DConfig>
#include <ostream>
#include <QHBoxLayout>
#include "hoverbutton.h"

QT_BEGIN_NAMESPACE
class QStackedLayout;
QT_END_NAMESPACE

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE
BEGIN_USER_NAMESPACE
class SelectingPage;
class LoadingPage;
class ContentPage;
class MainWindow : public DMainWindow
{
public:
    Q_PROPERTY(bool saveLastWindowSize READ saveLastWindowSize WRITE setSaveLastWindowSize)

    explicit MainWindow(QWidget *parent = nullptr);

    void showContents();
    void showSplash();
    void showSelect();

    QPointer<QGSettings> getWindowSettings();
    QPointer<DConfig> getDConfig();
    QPointer<DConfig> writeDConfig();
    QPointer<ContentPage> getContentPage();
public slots:
    void refresh();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QMap<QString, QWidget *> m_itemMap;
    QList<PluginInterface *> m_plugins;
    QGSettings *m_windowSettings;
    DConfig *m_dConfig;
    HoverButton *m_refreshButton;
    QWidget *m_contentFrame;
    LoadingPage *m_loadingPage;
    SelectingPage *m_selectingPage;
    ContentPage *m_contentPage;
    QStackedLayout *m_stackedLayout;
};

END_USER_NAMESPACE
