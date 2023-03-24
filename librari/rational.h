#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

int GCD(int a, int b);

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  int GetNumerator() const;
  int GetDenominator() const;

  void SetNumerator(int numerator);
  void SetDenominator(int denominator);

  Rational();
  Rational(int val);  // NOLINT
  Rational(int p, int q);
  Rational(const Rational& r);

  Rational operator-() const;
  Rational operator+() const;

  Rational& operator+=(const Rational& first);
  Rational& operator-=(const Rational& first);
  Rational& operator*=(const Rational& first);
  Rational& operator/=(const Rational& first);

  Rational& operator++();
  Rational operator++(int);

  Rational& operator--();
  Rational operator--(int);

 private:
  int p_ = 0;
  int q_ = 1;

  void Reduce();
};

std::istream& operator>>(std::istream& input, Rational& val);
std::ostream& operator<<(std::ostream& output, const Rational& val);

bool operator>(const Rational& first, const Rational& other);
bool operator<(const Rational& first, const Rational& other);
bool operator<=(const Rational& first, const Rational& other);
bool operator>=(const Rational& first, const Rational& other);
bool operator==(const Rational& first, const Rational& other);
bool operator!=(const Rational& first, const Rational& other);

Rational operator+(const Rational& first, const Rational& other);
Rational operator-(const Rational& first, const Rational& other);
Rational operator*(const Rational& first, const Rational& other);
Rational operator/(const Rational& first, const Rational& other);

#endif