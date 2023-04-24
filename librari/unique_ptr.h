#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>
#include "unique_ptr.h"

template <class T>
class UniquePtr {
 public:

  explicit UniquePtr() noexcept : ptr_(nullptr) {
  }

  explicit UniquePtr(T* other) noexcept : ptr_(other) {
  }

  UniquePtr(const UniquePtr<T>& other) = delete;

  UniquePtr& operator=(const UniquePtr<T>& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  T* Get() const {
    return ptr_;
  }

  void Reset(T* ptr = nullptr) {
    if (ptr_ != ptr) {
      delete ptr_;
    }

    ptr_ = ptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T* Release() {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Swap(UniquePtr<T>& other) {
    std::swap(ptr_, other.ptr_);
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  ~UniquePtr() {
    delete ptr_;
  }

 private:
  T* ptr_ = nullptr;
};

#endif