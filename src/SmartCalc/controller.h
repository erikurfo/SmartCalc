#ifndef CPP3_SMARTCALC_V_2_0_SMARTCALC_CONTROLLER_H_
#define CPP3_SMARTCALC_V_2_0_SMARTCALC_CONTROLLER_H_

#include "model.h"

namespace s21 {
class Controller {
 public:
  Controller(){};
  ~Controller(){};
  Controller(s21::Model* other) : model(other){};
  Controller& operator=(const Controller& other) {
    model = other.model;
    return *this;
  }

  double Calculator(std::string input, double X) {
    return model->Calculator(input, X);
  }

  double Graph_Calculator(double step) { return model->Decoding(step); }

 private:
  s21::Model* model;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V_2_0_SMARTCALC_CONTROLLER_H_
