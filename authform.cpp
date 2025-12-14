#include "authform.h"
#include "ui_authform.h"

AuthForm::AuthForm(QWidget* parent) : QWidget(parent), ui(new Ui::AuthForm) {
  ui->setupUi(this);
  connect(ui->enterButton, SIGNAL(clicked(bool)), this, SLOT(auth()));
}

AuthForm::~AuthForm() {
  delete ui;
}

void AuthForm::auth() {
  QString login;
  login = ui->login->text();
  ui->pass->setText(login + "hello");
}
