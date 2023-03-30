#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, size_t N> class array {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  array();
  ~array();
  explicit array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  array &operator=(array &&other);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  const_reference front() const;
  reference front();
  const_reference back() const;
  reference back();
  iterator data();
  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void swap(array &other);
  void fill(const_reference value);

private:
  void copy_array(const array &othet);
  value_type arr_[N];
};

#include "s21_array.tpp"

} // namespace s21
#endif
