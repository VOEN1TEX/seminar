#ifndef STRING_VIEW_H
#define STRING_VIEW_H
#include <stdexcept>
#include <iostream>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  StringView() = default;
  StringView(const char* ptr) noexcept;              // NOLINT
  StringView(const char* ptr, size_t len) noexcept;  // NOLINT

  const char& operator[](size_t index) const;

  const char& At(size_t index) const;
  const char& Front() const noexcept;
  const char& Back() const noexcept;
  const char* Data() const noexcept;

  size_t Size() const noexcept;
  size_t Length() const noexcept;

  bool Empty() const noexcept;

  void Swap(StringView& other) noexcept;

  void RemovePrefix(size_t prefix_size) noexcept;
  void RemoveSuffix(size_t suffix_size) noexcept;
  StringView Substr(size_t pos, size_t count) const;

 private:
  const char* ptr_ = nullptr;
  size_t len_ = 0;
};

#endif