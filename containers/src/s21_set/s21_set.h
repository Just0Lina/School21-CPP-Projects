#ifndef S21_SET_H
#define S21_SET_H
#include <fstream>

#include "../s21_map/s21_map.h"

namespace s21 {

template <typename Key, typename Value>
class SetIterator : public TreeConstIterator<const Key, Value> {
public:
  SetIterator();
  SetIterator(Node<Key, Value> *const &node, Node<Key, Value> *const &fake);
  explicit SetIterator(const TreeIterator<Key, Value> &iter);
  explicit SetIterator(const TreeConstIterator<Key, Value> &iter);
  SetIterator(const SetIterator<Key, Value> &it) = default;
  SetIterator(SetIterator<Key, Value> &&it) = default;
  SetIterator &operator=(const SetIterator<Key, Value> &it);
  const Key &operator*() const;
  bool operator==(const SetIterator<Key, Value> &iter) const;
  bool operator!=(const SetIterator<Key, Value> &iter) const;
  SetIterator &operator++();
  SetIterator operator++(int);
  SetIterator &operator--();
  SetIterator operator--(int);
};
#include "s21_set_iterator.tpp"

template <typename Key, typename Value = char>
class set : public map<Key, Value> {
public:
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  using iterator = SetIterator<const Key, Value>;
  using const_iterator = iterator;
  set();
  explicit set(const std::initializer_list<value_type> &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set &operator=(set &&s);
  iterator find(const value_type &key) const;
  typename std::pair<iterator, bool> insert(const value_type &value);

  iterator begin() const;
  iterator end() const;

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

  void print();

  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
};

} // namespace s21
#include "s21_set.tpp"
#endif
