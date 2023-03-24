#include "rational.h"

int GCD(int first, int second) {
  while (second != 0) {
    int store = second;
    second = first % second;
    first = store;
  }

  return first;
}

void Rational::Reduce() {
  if (q_ == 0) {
    throw RationalDivisionByZero();
  }

  int gcd = GCD(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    q_ = -q_;
    p_ = -p_;
  }
}

Rational::Rational(int p, int q) {
  p_ = p;
  q_ = q;

  Reduce();
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  SetDenominator(r.q_);
}

Rational::Rational() {
  p_ = 0;
  q_ = 1;
}

Rational::Rational(int val) {
  p_ = val;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int numerator) {
  p_ = numerator;
  Reduce();
}

void Rational::SetDenominator(int denominator) {
  q_ = denominator;
  Reduce();
}

Rational Rational::operator-() const {
  Rational copy = *this;
  copy.p_ = -copy.p_;
  return copy;
}

Rational Rational::operator+() const {
  return *this;
}

Rational& Rational::operator+=(const Rational& first) {
  p_ = p_ * first.q_ + first.p_ * q_;
  q_ = q_ * first.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator-=(const Rational& first) {
  p_ = p_ * first.q_ - first.p_ * q_;
  q_ = q_ * first.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator*=(const Rational& first) {
  p_ = p_ * first.p_;
  q_ = q_ * first.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& first) {
  p_ = p_ * first.q_;
  q_ = q_ * first.p_;
  Reduce();
  return *this;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

std::ostream& operator<<(std::ostream& output, const Rational& val) {
  output << val.GetNumerator();
  
  if (val.GetDenominator() != 1) {
    output << "/" << val.GetDenominator();
  }

  return output;
}

std::istream& operator>>(std::istream& input, Rational& val) {
  val = 0;
  int sign = 1;
  char input_string[50];
  input >> input_string;

  int i = 0;
  while (input_string[i] != 0 && input_string[i] != '/') {
    if (input_string[i] == '-') {
      sign *= -1;
    } else if (input_string[i] != '+') {
      val.SetNumerator(val.GetNumerator() * 10 + (input_string[i] - '0'));
    }
    ++i;
  }

  int denominator = 0;
  bool denominator_exists = false;

  while (input_string[i] != 0) {
    if (input_string[i] == '-') {
      sign *= -1;
    } else if (input_string[i] != '/' && input_string[i] != '+') {
      denominator_exists = true;
      denominator = denominator * 10 + (input_string[i] - '0');
    }
    ++i;
  }

  val.SetNumerator(val.GetNumerator() * sign);
  if (denominator == 0) {
    val.SetDenominator(denominator_exists ? 0 : 1);
  } else {
    val.SetDenominator(denominator);
  }
  return input;
}

Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}

Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}

Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}

Rational operator/(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy /= other;
  return copy;
}

bool operator>(const Rational& first, const Rational& other) {
  return (first.GetNumerator() * other.GetDenominator() > first.GetDenominator() * other.GetNumerator());
}

bool operator<(const Rational& first, const Rational& other) {
  return other > first;
}

bool operator==(const Rational& first, const Rational& other) {
  return (first.GetNumerator() * other.GetDenominator() == first.GetDenominator() * other.GetNumerator());
}

bool operator>=(const Rational& first, const Rational& other) {
  return (first > other || first == other);
}

bool operator<=(const Rational& first, const Rational& other) {
  return (first < other || first == other);
}

bool operator!=(const Rational& first, const Rational& other) {
  return !(first == other);
}