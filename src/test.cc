#include <gtest/gtest.h>

#include "./SmartCalc/model.h"

s21::Model model;

TEST(CalculatorTest, SimpleExpressions) {
  std::map<std::string, double> expressions = {
      {"(2 + 3) * 4", 20},
      {"2^3 - (5 + 1)", 2},
      {"0.3 * ((1.5 + 2.7) / 1.2)", 1.05},
      {"((4.2 - 1.7) * 2.9) + 0.5", 7.75},
      {"5.1 * (3.6 - (2.8 / 1.4))", 8.16}};
  for (const auto& [exp, res] : expressions) {
    double result = model.Calculator(exp, 0);
    ASSERT_NEAR(result, res, 1e-7);
  }
}

TEST(CalculatorTest, ExpressionsWithE) {
  std::map<std::string, double> expressions = {
      {"10^10 + 1e-5", 10000000000.00001},
      {" (5e-3 * 8e6) - 2e4 ", 20000},
      {"1e10 / (3e-5 + 2e-6)", 312500000000000},
      {"2e-10 * ((4e8 + 2e7) / 1e5)", 0.00000084},
      {"((1e-4 + 0.8) - (2e-3 * 5e-2)) / 0.2", 4}};
  for (const auto& [exp, res] : expressions) {
    double result = model.Calculator(exp, 0);
    ASSERT_NEAR(result, res, 1e-7);
  }
}

TEST(CalculatorTest, MiddleExpressions) {
  std::map<std::string, double> expressions = {
      {"sin(0.5) + cos(1.2)", 0.841783293081},
      {"sqrt(5 + log(10))", 2.4494897427831781},
      {"cos(sqrt(2)) - tan(0.7)", -0.686344685698},
      {"-sqrt(10 - log(2)) + acos(0.6)", -2.1870217222492678},
      {"3.6345mod(atan(sqrt(3.7)) + ln(8.2))", 0.4389906044877926}};
  for (const auto& [exp, res] : expressions) {
    double result = model.Calculator(exp, 0);
    ASSERT_NEAR(result, res, 1e-7);
  }
}

TEST(CalculatorTest, DifficultExpressions) {
  std::map<std::string, double> expressions = {
      {"sin(sqrt(2) * cos(log(3) + tan(0.7))) - ln(5mod(sqrt(2 + cos(1.5))))",
       0.7258561929423},
      {"ln(atan(-4.5e-3) * sin(2.5e6mod4.2e3 * tan(1.8e-2)))/(-1.52356341)",
       3.7358235774689561},
      {"((cos(2.1e-2) - atan(3.4e-1))^2 + sqrt((sin(4.5e-3))^3)) / "
       "(log(sin(3.1e2)) * (ln(asin(8.93e-1))))",
       -65.1552131862996149},
      {"sin(cos(tan(atan(acos(1/asin(sqrt(ln(log(123.2413513413)))))))))",
       0.823832196202},
      {"-sin(-cos(-tan(-atan(acos(1/asin(-sqrt(ln(log(123.2413513413)))))))))",
       -0.823832196203}};
  for (const auto& [exp, res] : expressions) {
    double result = model.Calculator(exp, 0);
    ASSERT_NEAR(result, res, 1e-7);
  }
}

TEST(CalculatorTest, ExpressionsWithX) {
  std::map<std::pair<std::string, double>, double> expressions = {
      {{"sqrt(X)", 9}, 3},
      {{"((4.2 - 1.7) * X^2) + 0.5", sqrt(2.9)}, 7.75},
      {{"2e-10 * ((4e8 + X) / 1e5)", 2e7}, 0.00000084},
      {{"Xmod(atan(sqrt(3.7)) + ln(8.2))", 3.6345}, 0.4389906044877926},
      {{"ln(atan(-4.5e-3) * sin(2.5e6modX * tan(1.8e-2)))/(-1.52356341) + X",
        4.2e3},
       4203.7358235774689561}};
  for (const auto& [exp, res] : expressions) {
    double result = model.Calculator(exp.first, exp.second);
    ASSERT_NEAR(result, res, 1e-7);
  }
}

TEST(CalculatorTest, Exceptions) {
  std::vector<std::string> expressions = {
      "10^.10 + 1e-5", " (5e-3 * 8e6) - 2e4 )))",
      "fykrrtsn",      "sincostanatan",
      "((((()))))",    ")()",
      "sin",           "-----134",
      "23+-",          "mod4",
      "XXX.com",       "1.2.3.4.5",
      "1.35sin(30)",   "acos+45",
      "1ein(2352)",    "/mod2"};
  for (const auto& exp : expressions) {
    EXPECT_ANY_THROW(model.Calculator(exp, 0));
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}