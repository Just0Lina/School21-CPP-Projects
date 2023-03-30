#ifndef S21_MULTISET_H
#define S21_MULTISET_H
#include "../s21_set/s21_set.h"
#include "../s21_vector/s21_vector.h"
namespace s21 {
template <typename Key, typename Value = char>
class multiset : public set<Key, Value> {
public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  using iterator = SetIterator<const Key, Value>;
  using const_iterator = iterator;

  multiset();
  explicit multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset();
  multiset &operator=(multiset &&ms);

  template <typename... Args> vector<iterator> emplace(Args &&...args);

  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);
  size_type count(const Key &key);
  iterator find(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);
};
} // namespace s21
#include "s21_multiset.tpp"
#endif