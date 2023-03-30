#ifndef S21_STACK_H
#define S21_STACK_H
#include <iostream>

#include "../s21_linked_list.h"

namespace s21 {
template <class T>

class stack {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = s21::Node<T>;

  stack();
  stack(const stack &s);
  explicit stack(std::initializer_list<value_type> const &items);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack<value_type> &&other);
  stack &operator=(const stack<value_type> &other);

  void push(const_reference val);
  void pop();
  bool empty() const;
  size_type size() const;
  const_reference top() const;
  void swap(stack &other);

  template <typename... Args> void emplace_front(Args &&...args);

private:
  size_type size_;
  Node *top_node_ = nullptr;

  void destroy();
};

#include "s21_stack.tpp"
} // namespace s21

#endif
