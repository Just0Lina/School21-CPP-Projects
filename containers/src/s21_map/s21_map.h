#ifndef S21_MAP_H
#define S21_MAP_H
#include "../s21_tree/s21_tree.h"
#include "../s21_vector/s21_vector.h"
namespace s21 {
template <typename Key, typename Value> class map : public rb_tree<Key, Value> {
public:
  using mapped_type = Value;
  using key_type = Key;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = TreeIterator<const Key, Value>;
  using const_iterator = TreeConstIterator<const Key, Value>;
  map() = default;
  explicit map(const std::initializer_list<value_type> &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map &operator=(map &&m);
  void print_map();

  iterator begin() const;

  mapped_type &at(const Key &key);
  mapped_type &operator[](const Key &key);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const Value &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

#include "s21_map.tpp"
} // namespace s21
#endif
