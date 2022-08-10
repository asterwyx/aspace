// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "echoeditor.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtGlobal>
BEGIN_USER_NAMESPACE
class EchoEditorPrivate {

public:
  explicit EchoEditorPrivate(EchoEditor *q);
  ~EchoEditorPrivate();

private:
  QLineEdit *m_lineEdit;
  QLabel *m_label;
  QPushButton *m_button;
  QString m_buffer;
  Q_DECLARE_PUBLIC(EchoEditor)
  EchoEditor *q_ptr;
};
END_USER_NAMESPACE