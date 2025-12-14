#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>

namespace Ui {
class AuthForm;
}

class AuthForm : public QWidget {
  Q_OBJECT

 public:
  explicit AuthForm(QWidget* parent = nullptr);
  ~AuthForm();

 public slots:
  void auth();

 private:
  Ui::AuthForm* ui;
};

#endif  // AUTHFORM_H
