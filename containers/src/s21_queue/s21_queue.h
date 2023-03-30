#ifndef S21_QUEUE_H
#define S21_QUEUE_H
#include "../s21_linked_list.h"
namespace s21 {
template <typename T> class queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = s21::Node<T>;

public:
  queue();
  explicit queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  const_reference front() const;
  const_reference back() const;

  void push(const_reference val);
  void pop();
  void swap(queue &other);
  bool empty() const;
  size_type size() const;

  template <typename... Args> void emplace_back(Args &&...args);

private:
  size_type size_;
  Node *front_node_;
  Node *back_node_;

  void destroy();
};
#include "s21_queue.tpp"
} // namespace s21

#endif
