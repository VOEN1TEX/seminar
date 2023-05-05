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

int main() {
//  1. Создание объекта класса Rational с правильнымипараметрами:
  Rational r1(3, 4);
  assert(r1.GetNumerator() == 3);
  assert(r1.GetDenominator() == 4);

//  2. Создание объекта класса Rational с неправильным знаменателем:
  try {
    Rational r2(3, 0);
  } catch (const RationalDivisionByZero &e) {
    // Ожидаемое исключение
  } catch (...) {
    assert(false && "Ожидалось исключение RationalDivisionByZero");
  }

//  3. Приведение дроби к наименьшему знаменателю:
  Rational r3(-2, -4);
  assert(r3.GetNumerator() == 1);
  assert(r3.GetDenominator() == 2);

//  4. Сложение двух дробей:
  Rational r4(1, 2);
  Rational r5(1, 3);
  Rational r6 = r4 + r5;
  assert(r6.GetNumerator() == 5);
  assert(r6.GetDenominator() == 6);

//  5. Вычитание двух дробей:
  Rational r7(1, 2);
  Rational r8(1, 3);
  Rational r9 = r7 - r8;
  assert(r9.GetNumerator() == 1);
  assert(r9.GetDenominator() == 6);

//  6. Умножение двух дробей:
  Rational r10(1, 2);
  Rational r11(1, 3);
  Rational r12 = r10 * r11;
  assert(r12.GetNumerator() == 1);
  assert(r12.GetDenominator() == 6);

//  7. Деление двух дробей:
  Rational r13(1, 2);
  Rational r14(1, 3);
  Rational r15 = r13 / r14;
  assert(r15.GetNumerator() == 3);
  assert(r15.GetDenominator() == 2);

//  8. Сравнение двух дробей:
  Rational r16(1, 2);
  Rational r17(1, 3);
  assert(r16 > r17);
  assert(!(r16 < r17));
  assert(!(r16 == r17));
  assert((r16 != r17));

//  9. Преобразование дроби в строку:
  Rational r18(3, 4);
  std::stringstream ss;
  ss << r18;
  assert(ss.str() == "3/4");

//  10. Создание объекта класса Rational с отрицательным знаменателем:
  Rational r19(3, -4);
  assert(r19.GetNumerator() == -3);
  assert(r19.GetDenominator() == 4);

//  11. Приведение дроби к наименьшему знаменателю при отрицательном числителе:
  Rational r20(-2, 4);
  assert(r20.GetNumerator() == -1);
  assert(r20.GetDenominator() == 2);

//  12. Сложение положительной и отрицательной дробей:
  Rational r21(1, 2);
  Rational r22(-1, 3);
  Rational r23 = r21 + r22;
  assert(r23.GetNumerator() == 1);
  assert(r23.GetDenominator() == 6);

//  13. Вычитание отрицательной дроби из положительной:
  Rational r24(-1, 3);
  Rational r25(1, 2);
  Rational r26 = r25 - r24;
  assert(r26.GetNumerator() == 5);
  assert(r26.GetDenominator() == 6);

//  14. Умножение отрицательной дроби на положительную:
  Rational r27(-1, 2);
  Rational r28(1, 3);
  Rational r29 = r27 * r28;
  assert(r29.GetNumerator() == -1);
  assert(r29.GetDenominator() == 6);

//  15. Деление положительной дроби на отрицательную:
  Rational r30(1, 2);
  Rational r31(-1, 3);
  Rational r32 = r30 / r31;
  assert(r32.GetNumerator() == -3);
  assert(r32.GetDenominator() == 2);

//  16. Сравнение двух равных дробей:
  Rational r33(2, 4);
  Rational r34(1, 2);
  assert(r33 == r34);
  assert(!(r33 < r34));
  assert(!(r33 > r34));

//  17. Сравнение двух неравных дробей:
  Rational r35(1, 2);
  Rational r36(1, 3);
  assert(r35 > r36);
  assert(!(r35 < r36));
  assert(!(r35 == r36));

//  18. Преобразование отрицательной дроби в строку:
  Rational r37(-3, 4);
  std::stringstream ss2;
  ss2 << r37;
  assert(ss2.str() == "-3/4");

//  19. Приведение дроби к наименьшему знаменателю при положительном числителе и отрицательном знаменателе:
  Rational r38(2, -6);
  assert(r38.GetNumerator() == -1);
  assert(r38.GetDenominator() == 3);

//  20. Вычитание двух отрицательных дробей с разными знаменателями:
  Rational r39(-2, 5);
  Rational r40(-1, 3);
  Rational r41 = r39 - r40;
  assert(r41.GetNumerator() == -1);
  assert(r41.GetDenominator() == 15);

//  21. Умножение положительной дроби на отрицательное целое число:
  Rational r42(1, 3);
  int n3 = -4;
  Rational r43 = r42 * n3;
  assert(r43.GetNumerator() == -4);
  assert(r43.GetDenominator() == 3);

//  22. Деление отрицательной дроби на положительное целое число:
  Rational r44(-1, 3);
  int n4 = 4;
  Rational r45 = r44 / n4;
  assert(r45.GetNumerator() == -1);
  assert(r45.GetDenominator() == 12);

//  23.Сравнение двух равных дробей с одинаковыми отрицательными числителями и знаменателями:
  Rational r46(1, -2);
  Rational r47(2, -4);
  assert(r46 == r47);
  assert(!(r46 < r47));
  assert(!(r46 > r47));

//  24. Сравнение двух неравных дробей с разными числителями и знаменателями, одна из которых отрицательная:
  Rational r48(-1, 2);
  Rational r49(2, 3);
  assert(r48 < r49);
  assert(!(r48 > r49));
  assert(!(r48 == r49));

//  25. Приведение дроби к наименьшему знаменателю при одинаковых числителе и разных знаменателях с положительными значениями:
  Rational r50(1, 2);
  Rational r51(1, 4);
  assert(r50.GetNumerator() == 1);
  assert(r50.GetDenominator() == 2);
  assert(r51.GetNumerator() == 1);
  assert(r51.GetDenominator() == 4);

//  26. Сложение двух положительных дробей с разными знаменателями:
  Rational r52(1, 3);
  Rational r53(2, 5);
  Rational r54 = r52 + r53;
  assert(r54.GetNumerator() == 11);
  assert(r54.GetDenominator() == 15);

// 27. Сравнение
  Rational r55(1, 3);
  Rational r56(2, 5);
  Rational r57(1, 15);
  assert(!(r55 == r56));
  assert(r55 == (r56 - r57));

// 28. Проверка инкремента
  Rational r58(2, 3);
  Rational r59(3, 4);
  assert(++r58 == Rational(5, 3));
  assert(r58++ == Rational(5, 3));
  assert(r58 == Rational(8, 3));

// 29. Проверка декремента
  assert(--r59 == Rational(-1, 4));
  assert(r59-- == Rational(-1, 4));
  assert(r59 == Rational(-5, 4));

//30. Сложное выражение
  Rational r60(6, 9);
  assert(r59-- + --r60 == Rational(-19, 12));
//31. Ввод и вывод
  Rational a, b;
  std::cout << "Write -12/144 2\n";
  std::cin >> a >> b;
  assert(a == Rational(-1,12));
  assert(b == Rational(2));

  std::cout << "OK";
  return 0;
}