#pragma once
#include "common_def.h"
#include "page.h"

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;
QT_END_NAMESPACE



class SelectingPage : public Page
{
    Q_OBJECT
public:
    SelectingPage(MainWindow *parent = nullptr);

signals:
    void citySelected(const QString &cityCode);

private slots:
    void onConfirmed();

private:
    QGroupBox *m_inputBox;
    QVBoxLayout *m_contentLayout;
    QLabel *m_welcomeLabel;
    QLabel *m_hintLabel;
    QLineEdit *m_cityLineEdit;
    QPushButton *m_confirmButton;
    QLabel *m_resultLabel;  // display error message
};
