#pragma once
#include "common_def.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>



class LoadingPage : public QWidget
{
public:
    LoadingPage(QWidget *parent = nullptr);

private:
    QVBoxLayout *m_layout;
    QLabel *m_loadingLabel;
};
