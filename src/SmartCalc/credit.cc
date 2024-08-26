#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  connect(ui->result, SIGNAL(released()), this, SLOT(credit_calc()));
}

Credit::~Credit() { delete ui; }

void Credit::credit_calc() {
  double summ, out, overpay, monthly, percent;
  int term;
  summ = ui->sumcredit->text().toDouble();
  term = ui->loan_term->text().toInt();
  percent = ui->percent->text().toDouble();
  if (ui->annuit->isChecked()) {
    percent = percent / 1200;
    monthly = summ * (percent * pow((1 + percent), term) /
                      (pow((1 + percent), term) - 1));
    overpay = monthly * term - summ;
    out = overpay + summ;
    QString qsum = QString::number(out, 'f', 2);
    QString qmonth = QString::number(monthly, 'f', 2);
    QString qover = QString::number(overpay, 'f', 2);
    ui->all_sum->setText(qsum);
    ui->percent_pay->setText(qover);
    ui->month_pay->setText(qmonth);
  } else if (ui->diff->isChecked()) {
    out = 0;
    int debt_sum = summ / term;
    double buf_sum = summ;
    monthly = (summ * percent / 100 * 30.4166666666667 / 365) + debt_sum;
    QString qmonth = QString::number(monthly, 'f', 2);
    ui->month_pay->setText(qmonth + " ... ");
    for (int i = 0; i < term; i++) {
      monthly = (buf_sum * percent / 100 * 30.4166666666667 / 365) + debt_sum;
      buf_sum = buf_sum - debt_sum;
      out = out + monthly;
    }
    qmonth = QString::number(monthly, 'f', 2);
    ui->month_pay->setText(ui->month_pay->text() + qmonth);
    overpay = out - debt_sum * term;
    QString qsum = QString::number(out, 'f', 2);
    QString qover = QString::number(overpay, 'f', 2);
    ui->all_sum->setText(qsum);
    ui->percent_pay->setText(qover);
  }
}
