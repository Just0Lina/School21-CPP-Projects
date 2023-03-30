#ifndef S21_LIST_H
#define S21_LIST_H
#include <iostream>

namespace s21 {
template <typename T> struct D_Node {
  T value_{};
  struct D_Node *next_{};
  struct D_Node *prev_{};
};

template <typename T> class ListIterator {
public:
  ListIterator();
  explicit ListIterator(D_Node<T> *pos);
  T &operator*();
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  bool operator!=(const ListIterator &rhs) const;
  bool operator==(const ListIterator &rhs) const;

  D_Node<T> *pos_ = nullptr;
};

template <typename T> class ListConstIterator {
public:
  explicit ListConstIterator(const ListIterator<T> &iter);
  ListConstIterator &operator++();
  ListConstIterator operator++(int);
  ListConstIterator &operator--();
  ListConstIterator operator--(int);
  const T &operator*() const;
  bool operator!=(const ListConstIterator<T> &rhs) const;
  bool operator==(const ListConstIterator<T> &rhs) const;

  const D_Node<T> *pos_ = nullptr;
};

template <typename T> class list {
public:
  using Node = D_Node<T>;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();

  list &operator=(list &&l);

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;
  unsigned long max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  iterator begin() const;
  iterator end() const;
  void push_back(const_reference value);
  void pop_back();
  void push_front(const T &val);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args> void emplace_back(Args &&...args);
  template <typename... Args> void emplace_front(Args &&...args);

private:
  size_type size_;
  Node *fake_node_;
  Node *front_node_;
  Node *back_node_;
  void addFake();
};
#include "s21_list.tpp"
#include "s21_list_const_iterator.tpp"
#include "s21_list_iterator.tpp"
} // namespace s21
#endif
