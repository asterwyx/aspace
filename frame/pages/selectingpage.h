#pragma once
#include "common_def.h"
#include "page.h"

BEGIN_USER_NAMESPACE

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
    QHBoxLayout *m_lineEditLayout;
    QLabel *m_welcomeLabel;
    QLabel *m_hintLabel;
    QLabel *m_resultLabel;  // display error message
    QLineEdit *m_cityLineEdit;
    QPushButton *m_confirmButton;
};

END_USER_NAMESPACE