#include "mainwindow.h"

#include "credit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::Controller *ctrl)
    : QMainWindow(parent), controller(ctrl), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->equal, SIGNAL(released()), this, SLOT(equal()));
  connect(ui->AC, SIGNAL(released()), this, SLOT(AC()));
  connect(ui->graph, SIGNAL(released()), this, SLOT(graph()));
  connect(ui->credit, SIGNAL(released()), this, SLOT(credit_calc()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::equal() {
  try {
    std::string string = ui->text->text().toStdString();

    double result =
        controller->Calculator(string, ui->X_field->text().toDouble());

    ui->text->setText(QString::number(result));
    ui->error_label->setText("");
  } catch (const std::exception &e) {
    ui->error_label->setText(e.what());
  }
}

void MainWindow::AC() {
  ui->text->setText("");
  ui->error_label->setText("");
}

void MainWindow::graph() {
  try {
    std::string string = ui->text->text().toStdString();
    xBegin = ui->Xmin->text().toDouble();
    xEnd = ui->Xmax->text().toDouble();
    h = (xEnd - xBegin) / 1000;
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(ui->Ymin->text().toDouble(),
                                ui->Ymax->text().toDouble());
    // Для получения польской нотации
    controller->Calculator(string, 0);

    for (step = xBegin; step <= xEnd; step += h) {
      double result = controller->Graph_Calculator(step);
      x.push_back(step);
      y.push_back(result);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->widget->graph(0)->data()->clear();
    x.clear(), y.clear();

    ui->error_label->setText("");
  } catch (const std::exception &e) {
    ui->error_label->setText(e.what());
  }
}

void MainWindow::credit_calc() {
  Credit credit_calc;
  credit_calc.setModal(true);
  credit_calc.exec();
}
