#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N = 0>
class Array {
 public:
  T array_[N];
  size_t Size() const noexcept {
    return N;
  }
  const T& operator[](size_t index) const {
    return array_[index];
  }

  T& operator[](size_t index) {
    return array_[index];
  }

  const T& At(size_t index) const {
    if (index >= N) {
      throw ArrayOutOfRange();
    }
    return array_[index];
  }

  T& At(size_t index) {
    if (index >= N) {
      throw ArrayOutOfRange();
    }
    return array_[index];
  }

  bool Empty() const noexcept {
    return (N == 0);
  }

  void Fill(const T& value) noexcept {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = value;
    }
  }

  T* Data() noexcept {
    return &array_[0];
  }

  const T* Data() const noexcept {
    return &array_[0];
  }

  void Swap(Array<T, N>& other) noexcept {
    std::swap(array_, other.array_);
  }

  const T& Front() const noexcept {
    return *array_;
  }

  T& Front() noexcept {
    return *array_;
  }

  const T& Back() const noexcept {
    return array_[N - 1];
  }

  T& Back() noexcept {
    return array_[N - 1];
  }
};

#endif