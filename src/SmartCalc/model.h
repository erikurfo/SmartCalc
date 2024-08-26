#ifndef CPP3_SMARTCALC_V_2_0_SMARTCALC_MODEL_H_
#define CPP3_SMARTCALC_V_2_0_SMARTCALC_MODEL_H_

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace s21 {
class Model {
 public:
  Model() {}
  ~Model() {}
  Model(const Model& other) {
    input_ = other.input_;
    postfix_notation = other.postfix_notation;
  }
  Model& operator=(const Model& other) {
    input_ = other.input_;
    postfix_notation = other.postfix_notation;
    return *this;
  }

  double Calculator(const std::string input_string, double X);
  double Decoding(double X) const noexcept;

 private:
  void SetInput(const std::string text) noexcept { input_ = text; };
  Model Convertation();
  Model Validation() const;
  Model PolishNotation();

  double MakeOperations(const double number_1, const double number_2,
                        const char sym) const noexcept;
  double MakeOperations(const double number, const char sym) const noexcept;
  int Priority(const char op) const noexcept;
  void Protection();
  const std::string letters = "abcdkfghi";
  const std::string operators = "+-*/%^";
  void RegexValid() const;
  int LexemeType(const char sym) const;

  const int arr[10][10] = {
      {1, 1, 0, 1, 0, 1, 1, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 0, 1, 0, 0, 0, 1, 0}, {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}};

  enum Symbol {
    NUMBER,
    DOT,
    LETTERS,
    OPERATORS,
    OP_BRACE,
    CL_BRACE,
    E,
    EOS,
    X,
    PLUS_MINUS
  };

 private:
  std::string input_;
  std::vector<std::variant<char, double>> postfix_notation;
};
}  // namespace s21

#endif  //  CPP3_SMARTCALC_V_2_0_SMARTCALC_MODEL_H_
