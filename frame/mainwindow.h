#pragma once

#include <DMainWindow>
#include <QMap>
#include <QPair>
#include <QGSettings>
#include <DConfig>
#include <ostream>
#include <QHBoxLayout>
#include "hoverbutton.h"
class QStackedLayout;
DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

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
    QGSettings *m_windowSettings;
    DConfig *m_dConfig;
    HoverButton *m_refreshButton;
    QWidget *m_contentFrame;
    LoadingPage *m_loadingPage;
    SelectingPage *m_selectingPage;
    ContentPage *m_contentPage;
    QStackedLayout *m_stackedLayout;
};
