#include "s21_array.h"

template <typename T, size_t N> array<T, N>::array() {}

template <typename T, size_t N> array<T, N>::~array() {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  int i = 0;
  for (value_type x : items) {
    arr_[i] = x;
    ++i;
  }
}

template <typename T, size_t N> array<T, N>::array(const array &other) {
  copy_array(other);
}

template <typename T, size_t N>
array<T, N>::array(array &&other) : array(other) {}

template <typename T, size_t N>
void array<T, N>::copy_array(const array &other) {
  for (size_t i = 0; i < N; ++i) {
    arr_[i] = other.arr_[i];
  }
}

template <typename T, size_t N> T &array<T, N>::operator[](size_t pos) {
  return arr_[pos];
}

template <typename T, size_t N>
const T &array<T, N>::operator[](size_t pos) const {
  return arr_[pos];
}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&other) {
  if (this == &other) {
    return *this;
  }
  copy_array(other);
  return *this;
}

template <typename T, size_t N> const T &array<T, N>::at(size_t pos) const {
  if (pos >= N) {
    throw std::out_of_range("Error: out of range");
  }
  return arr_[pos];
}
template <typename T, size_t N> T &array<T, N>::at(size_t pos) {
  if (pos >= N) {
    throw std::out_of_range("Error: out of range");
  }
  return arr_[pos];
}

template <typename T, size_t N> const T &array<T, N>::front() const {
  return arr_[0];
}

template <typename T, size_t N> T &array<T, N>::front() { return arr_[0]; }

template <typename T, size_t N> const T &array<T, N>::back() const {
  if (N > 0)
    return arr_[N - 1];
  return arr_[N];
}

template <typename T, size_t N> T &array<T, N>::back() {
  if (N > 0)
    return arr_[N - 1];
  return arr_[N];
}

template <typename T, size_t N> T *array<T, N>::data() { return &arr_[0]; }

template <typename T, size_t N> T *array<T, N>::begin() { return &arr_[0]; }

template <typename T, size_t N> T *array<T, N>::end() { return &arr_[N]; }

template <typename T, size_t N> bool array<T, N>::empty() const { return !N; }

template <typename T, size_t N> size_t array<T, N>::size() const { return N; }

template <typename T, size_t N> size_t array<T, N>::max_size() const {
  return size();
}

template <typename T, size_t N> void array<T, N>::swap(array &other) {
  std::swap(arr_, other.arr_);
}

template <typename T, size_t N> void array<T, N>::fill(const T &value) {
  for (size_t i = 0; i < N; ++i) {
    arr_[i] = value;
  }
}
