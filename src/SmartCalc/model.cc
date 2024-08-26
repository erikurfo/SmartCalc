#include "model.h"

s21::Model s21::Model::Convertation() {
  RegexValid();
  Protection();
  input_ = "(" + input_ + ")";
  input_.erase(std::remove(input_.begin(), input_.end(), ' '), input_.end());
  std::map<std::string, std::string> FunctionMap = {
      {"sin", "a"},  {"cos", "b"},      {"tan", "c"},  {"asin", "d"},
      {"acos", "k"}, {"atan", "f"},     {"sqrt", "g"}, {"ln", "h"},
      {"log", "i"},  {"(-", "(0-"},     {"(+", "(0+"}, {"+-", "-"},
      {"-+", "-"},   {"--", "+"},       {"++", "+"},   {"mod", "%"},
      {")(", ")*("}, {"*-", "*(0-1)*"}, {"*+", "*"}};
  for (const auto& [function, letter] : FunctionMap) {
    size_t position = 0;
    while ((position = input_.find(function, position)) != std::string::npos) {
      input_.replace(position, function.length(), letter);
      position += 1;
    }
  }
  return *this;
}

void s21::Model::Protection() {
  for (char& c : input_) c = std::tolower(c);
  int count_op_br = 0, count_cl_br = 0;
  for (char c : input_) {
    if (c == '(') count_op_br++;
    if (c == ')') count_cl_br++;
    if (count_cl_br > count_op_br)
      throw std::logic_error("Некорректная постановка скобок!");
  }
  if (count_op_br != count_cl_br)
    throw std::logic_error("Добавьте закрывающую скобку!");
}

void s21::Model::RegexValid() const {
  std::regex regex("^[0-9a-zA-Z\\+\\-\\*/%\\^\\(\\)\\.\\s]+$");
  if (!std::regex_match(input_, regex))
    throw std::logic_error("Некорректная запись!");
  if (input_[0] == ')' || input_[0] == '*' || input_[0] == '/' ||
      input_[0] == '%' || input_[0] == '^')
    throw std::logic_error("Некорректная запись!");
  if (input_[0] == 'm' && input_[1] == 'o' && input_[2] == 'd')
    throw std::logic_error("Некорректная запись!");
}

int s21::Model::LexemeType(const char sym) const {
  if (sym == '\0') return EOS;
  if (isdigit(sym)) return NUMBER;
  if (sym == '+' || sym == '-') return PLUS_MINUS;
  if (letters.find(sym) != std::string::npos) return LETTERS;
  if (operators.find(sym) != std::string::npos) return OPERATORS;
  if (sym == '(') return OP_BRACE;
  if (sym == ')') return CL_BRACE;
  if (sym == '.') return DOT;
  if (sym == 'e') return E;
  if (sym == 'x') return X;
  throw std::logic_error("Некорректная запись!");
  return 0;
}

s21::Model s21::Model::Validation() const {
  bool result = true;
  for (size_t i = 0; i < input_.length(); ++i) {
    int current = LexemeType(input_[i]);
    int next = LexemeType(input_[i + 1]);
    result &= arr[current][next];
    if (!result) throw std::logic_error("Некорректная запись!");
  }
  return *this;
}

int s21::Model::Priority(const char op) const noexcept {
  int result = 0;
  std::map<char, int> FunctionMap = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
                                     {'%', 2}, {'^', 3}, {'a', 4}, {'b', 4},
                                     {'c', 4}, {'d', 4}, {'k', 4}, {'f', 4},
                                     {'g', 4}, {'h', 4}, {'i', 4}};
  for (const auto& [symbol, value] : FunctionMap) {
    if (symbol == op) {
      result = value;
      break;
    }
  }
  return result;
}

s21::Model s21::Model::PolishNotation() {
  std::stack<char> Stack;
  const std::string operations = "+-*/%^()abcdkfghi";
  const char* exp = input_.c_str();
  char* end{};
  int priority_new = 0, priority_prev = 0;
  while (*exp) {
    double d = std::strtod(exp, &end);
    if (isdigit(*exp)) {
      exp = end;
      postfix_notation.push_back(d);
      if (*end == '\0') break;
      if (*end == '.') throw std::logic_error("Некорректная запись!");
    }
    if (*exp == 'x') postfix_notation.push_back(*exp), exp++;
    if (operations.find(*exp) != std::string::npos) {
      if (*exp == '(') {
        Stack.push(*exp);
      } else if (*exp == ')') {
        while (!Stack.empty() && Stack.top() != '(') {
          postfix_notation.push_back(Stack.top());
          Stack.pop();
        }
        if (!Stack.empty()) Stack.pop();
      } else {
        if (!Stack.empty()) priority_prev = Priority(Stack.top());
        priority_new = Priority(*exp);
        while (priority_new <= priority_prev && !Stack.empty()) {
          postfix_notation.push_back(Stack.top());
          Stack.pop();
          if (!Stack.empty()) priority_prev = Priority(Stack.top());
        }
        Stack.push(*exp);
      }
      exp++;
    }
  }
  while (!Stack.empty()) {
    postfix_notation.push_back(Stack.top());
    Stack.pop();
  }
  return *this;
}

double s21::Model::MakeOperations(const double number_1, const double number_2,
                                  const char sym) const noexcept {
  double result = 0;
  std::map<char, double> FunctionMap = {
      {'+', number_1 + number_2},      {'-', number_1 - number_2},
      {'*', number_1 * number_2},      {'/', number_1 / number_2},
      {'%', fmod(number_1, number_2)}, {'^', pow(number_1, number_2)}};
  for (const auto& [symbol, value] : FunctionMap) {
    if (symbol == sym) {
      result = value;
      break;
    }
  }
  return result;
}

double s21::Model::MakeOperations(const double number,
                                  const char sym) const noexcept {
  double result = 0;
  std::map<char, double> FunctionMap = {
      {'a', sin(number)},  {'b', cos(number)},  {'c', tan(number)},
      {'d', asin(number)}, {'k', acos(number)}, {'f', atan(number)},
      {'g', sqrt(number)}, {'h', log(number)},  {'i', log10(number)}};
  for (const auto& [symbol, value] : FunctionMap) {
    if (symbol == sym) {
      result = value;
      break;
    }
  }
  return result;
}

double s21::Model::Decoding(double X) const noexcept {
  std::stack<double> Stack;
  double number1 = 0, number2 = 0, result = 0;
  for (size_t i = 0; i < postfix_notation.size(); ++i) {
    if (std::holds_alternative<char>(postfix_notation[i])) {
      char sym = std::get<char>(postfix_notation[i]);
      if (operators.find(sym) != std::string::npos) {
        number1 = Stack.top(), Stack.pop();
        number2 = Stack.top(), Stack.pop();
        result = MakeOperations(number2, number1, sym);
        Stack.push(result);
      } else if (letters.find(sym) != std::string::npos) {
        number1 = Stack.top(), Stack.pop();
        result = MakeOperations(number1, sym);
        Stack.push(result);
      } else if (sym == 'x') {
        Stack.push(X);
      }
    } else {
      Stack.push(std::get<double>(postfix_notation[i]));
    }
  }
  result = Stack.top(), Stack.pop();
  return result;
}

double s21::Model::Calculator(std::string input_string, double X) {
  SetInput(input_string);
  *this = Convertation().Validation().PolishNotation();
  return Decoding(X);
}
