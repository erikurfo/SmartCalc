#ifndef CPP3_SMARTCALC_V_2_0_SMARTCALC_MAINWINDOW_H_
#define CPP3_SMARTCALC_V_2_0_SMARTCALC_MAINWINDOW_H_

#include <QMainWindow>
#include <QVector>
#include <QtWidgets>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, s21::Controller *ctrl = nullptr);
  ~MainWindow();

 private slots:
  void equal();
  void AC();
  void graph();
  void credit_calc();

 private:
  s21::Controller *controller;
  Ui::MainWindow *ui;
  double xBegin, xEnd, h, step;
  QVector<double> x, y;
};
#endif  // CPP3_SMARTCALC_V_2_0_SMARTCALC_MAINWINDOW_H_
