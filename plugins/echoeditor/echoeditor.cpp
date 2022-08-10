// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "echoeditor.h"
#include "echoeditor_p.h"
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QtGlobal>
#include <QString>

BEGIN_USER_NAMESPACE

EchoEditor::EchoEditor() : d_ptr(new EchoEditorPrivate(this)) {}

EchoEditor::~EchoEditor() = default;

QString EchoEditor::pluginName() const { return {"echo-editor"}; }
QString EchoEditor::pluginDisplayName() const { return {"Echo Editor"}; }

QWidget *EchoEditor::pluginWidget(const QString &key) {
    Q_UNUSED(key)
    Q_D(EchoEditor);
    auto *box = new QGroupBox();
    box->setGeometry(0, 0, 150, 50);
    auto *label = new QLabel(box);
    label->setGeometry(0, 25, 150, 25);
    label->setText(d->m_buffer);
    auto *lineEdit = new QLineEdit(box);
    lineEdit->setGeometry(0, 0, 100, 25);
    lineEdit->setText(d->m_buffer);
    auto *button = new QPushButton(box);
    button->setGeometry(100, 0, 50, 25);
    connect(button, &QPushButton::clicked, [=](bool checked) {
        Q_UNUSED(checked)
        d->m_buffer = lineEdit->text();
        label->setText(d->m_buffer);
    });
    return box;
}

EchoEditorPrivate::EchoEditorPrivate(EchoEditor *q) : q_ptr(q) {}

EchoEditorPrivate::~EchoEditorPrivate() = default;

END_USER_NAMESPACE