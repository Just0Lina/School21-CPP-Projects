#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T> class vector {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  vector();
  ~vector();
  explicit vector(size_type n);
  vector(const vector &other);
  vector(vector &&other);
  explicit vector(std::initializer_list<value_type> const &items);
  vector &operator=(vector &&other);
  reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  const_iterator data() const;
  iterator data();

  bool empty() const;
  size_type size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  iterator begin() const;
  iterator end() const;
  void clear();
  iterator insert(iterator pos, const_reference value);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);
  size_type max_size() const;
  void erase(iterator pos);

  template <typename... Args> iterator emplace(iterator pos, Args &&...args);
  template <typename... Args> void emplace_back(Args &&...args);

private:
  void memory_allocation();
  void destroy_vector();
  void copy_vector(const vector &other);
  void shift(const_iterator pos, size_t len);

  size_type size_;
  size_type capacity_;
  value_type *arr_;
};

#include "s21_vector.tpp"

} // namespace s21

#endif