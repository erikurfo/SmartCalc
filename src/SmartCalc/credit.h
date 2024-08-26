#ifndef CPP3_SMARTCALC_V_2_0_SMARTCALC_CREDIT_H_
#define CPP3_SMARTCALC_V_2_0_SMARTCALC_CREDIT_H_

#include <QDialog>

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void credit_calc();

 private:
  Ui::Credit *ui;
};

#endif  // CPP3_SMARTCALC_V_2_0_SMARTCALC_CREDIT_H_
