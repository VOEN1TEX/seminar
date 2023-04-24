#include "string_view.h"

StringView::StringView(const char* ptr) noexcept {  // NOLINT
  ptr_ = ptr;
  
  while (ptr_[len_] != 0) {
    ++len_;
  }
}

StringView::StringView(const char* ptr, size_t len) noexcept {
  ptr_ = ptr;
  len_ = len;
}

const char& StringView::operator[](size_t index) const {
  return ptr_[index];
}

const char& StringView::At(size_t index) const {
  if (index >= len_) {
    throw StringViewOutOfRange();
  }

  return ptr_[index];
}

const char& StringView::Front() const noexcept {
  return *ptr_;
}

const char& StringView::Back() const noexcept {
  return ptr_[len_ - 1];
}

size_t StringView::Size() const noexcept {
  return len_;
}

size_t StringView::Length() const noexcept {
  return len_;
}

bool StringView::Empty() const noexcept {
  return len_ == 0;
}

const char* StringView::Data() const noexcept {
  return ptr_;
}

void StringView::Swap(StringView& other) noexcept {
  std::swap(*this, other);
}

void StringView::RemovePrefix(size_t prefix_size) noexcept {
  ptr_ += prefix_size;
  len_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) noexcept {
  len_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count = -1) const {
  if (pos >= len_) {
    throw StringViewOutOfRange();
  }

  StringView substr{ptr_ + pos, std::min(count, Size() - pos)};
  return substr;
}