#include "echoeditor.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtGlobal>
namespace dspace {
class EchoEditorPrivate {

public:
  EchoEditorPrivate(EchoEditor *q);
  ~EchoEditorPrivate();

private:
  QLineEdit *m_lineEdit;
  QLabel *m_label;
  QPushButton *m_button;
  QString m_buffer;
  Q_DECLARE_PUBLIC(EchoEditor)
  EchoEditor *q_ptr;
};
} // namespace dspace